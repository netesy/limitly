// native_font.hh — self-contained TrueType/OpenType coverage font engine.
//
// C++ port of the std/font Lymar pipeline (tables.lm + glyph.lm +
// rasterizer.lm) used by the VM-side renderers:
//   - src/runtime/software_graphics.hh  (headless software text)
//   - src/runtime/sokol/sokol_gfx_runtime.cpp (windowed GPU text)
//
// Scaling: px / (hhea.ascent - hhea.descent), matching std.font.
// Coverage rasterization uses the same non-zero-winding scanline approach as
// rasterizer.lm, with per-pixel x-overlap accumulation for horizontal AA.
//
// The font is non-owning: the caller keeps the file bytes alive.

#pragma once

#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

namespace LM::Runtime {

// Decode one UTF-8 codepoint; advances `p` past it. Invalid bytes yield the
// byte value itself (Latin-1 fallback), matching stb's byte-wise behavior for
// ASCII and improving on it for multi-byte sequences.
inline uint32_t utf8_next(const char*& p, const char* end) {
    const uint8_t* s = reinterpret_cast<const uint8_t*>(p);
    const uint8_t* e = reinterpret_cast<const uint8_t*>(end);
    if (s >= e) { p = end; return 0; }
    uint8_t c = *s;
    if (c < 0x80) { p += 1; return c; }
    uint32_t cp = 0;
    int need = 0;
    if ((c & 0xE0) == 0xC0) { cp = c & 0x1F; need = 1; }
    else if ((c & 0xF0) == 0xE0) { cp = c & 0x0F; need = 2; }
    else if ((c & 0xF8) == 0xF0) { cp = c & 0x07; need = 3; }
    else { p += 1; return c; }
    if (s + need >= e) { p = end; return c; }
    for (int i = 0; i < need; ++i) {
        uint8_t cc = s[1 + i];
        if ((cc & 0xC0) != 0x80) { p += 1; return c; }
        cp = (cp << 6) | (cc & 0x3F);
    }
    p += need + 1;
    return cp;
}

struct FontPoint {
    float x, y;
    bool on_curve;
};

struct FontSegment {
    float x0, y0, x1, y1;
};

struct GlyphOutline {
    bool empty = true;
    std::vector<std::vector<FontPoint>> contours;
};

struct GlyphBitmap {
    int width = 0;
    int height = 0;
    int x_offset = 0; // ink left edge, px, relative to pen (y-down space)
    int y_offset = 0; // ink top edge, px, relative to baseline (negative = above)
    std::vector<uint8_t> pixels; // width*height coverage 0..255, row-major
};

struct HMetrics { int advance = 0; int lsb = 0; };
struct KernEntry { uint16_t g1, g2; int16_t value; };

struct CmapFormat4 {
    bool valid = false;
    int seg_count = 0;
    std::vector<uint16_t> end_codes, start_codes, id_range_offsets;
    std::vector<int16_t> id_deltas;
    size_t id_range_offsets_base = 0; // absolute file offset of idRangeOffset[0]
};

struct CmapGroup { uint32_t start_char, end_char, start_glyph; };

class NativeFont {
public:
    const uint8_t* data = nullptr;
    size_t size = 0;
    bool valid = false;

    // head/hhea/maxp
    int units_per_em = 1000;
    int index_to_loc_format = 0;
    int num_glyphs = 0;
    int ascent = 0, descent = 0, line_gap = 0;
    int num_h_metrics = 0;

    // table offsets (absolute in file)
    size_t loca_offset = 0, glyf_offset = 0, hmtx_offset = 0;

    CmapFormat4 cmap4;
    std::vector<CmapGroup> cmap12_groups;
    bool has_cmap12 = false;

    std::vector<KernEntry> kern_pairs; // file order, binary-searched like tables.lm

    std::vector<HMetrics> hmtx_cache;

    // font_offset: TTC directory offset for font index (0 for plain TTF).
    bool init(const uint8_t* bytes, size_t len, int font_index = 0) {
        data = bytes; size = len;
        if (!bytes || len < 12) return false;

        uint32_t scalar = be32(0);
        size_t base = 0;
        if (scalar == 0x74746366u) { // 'ttcf'
            if (len < 12) return false;
            uint32_t num_fonts = be32(8);
            if (font_index < 0 || (uint32_t)font_index >= num_fonts) return false;
            base = be32(12 + font_index * 4);
            if (base + 12 > len) return false;
        }

        uint16_t num_tables = be16(base + 4);
        if (base + 12 + (size_t)num_tables * 16 > len) return false;

        auto find_table = [&](uint32_t tag) -> int64_t {
            for (int i = 0; i < num_tables; ++i) {
                size_t rec = base + 12 + (size_t)i * 16;
                if (be32(rec) == tag) return (int64_t)be32(rec + 8);
            }
            return -1;
        };

        int64_t head_off = find_table(0x68656164u); // 'head'
        int64_t hhea_off = find_table(0x68686561u); // 'hhea'
        int64_t maxp_off = find_table(0x6D617870u); // 'maxp'
        int64_t hmtx_off = find_table(0x686D7478u); // 'hmtx'
        int64_t loca_off = find_table(0x6C6F6361u); // 'loca'
        int64_t glyf_off = find_table(0x676C7966u); // 'glyf'
        int64_t cmap_off = find_table(0x636D6170u); // 'cmap'
        int64_t kern_off = find_table(0x6B65726Eu); // 'kern'

        if (head_off < 0 || hhea_off < 0 || maxp_off < 0 ||
            hmtx_off < 0 || loca_off < 0 || glyf_off < 0 || cmap_off < 0)
            return false;

        units_per_em = be16((size_t)head_off + 18);
        index_to_loc_format = (int16_t)be16((size_t)head_off + 50);
        num_glyphs = be16((size_t)maxp_off + 4);
        ascent = (int16_t)be16((size_t)hhea_off + 4);
        descent = (int16_t)be16((size_t)hhea_off + 6);
        line_gap = (int16_t)be16((size_t)hhea_off + 8);
        num_h_metrics = be16((size_t)hhea_off + 34);
        hmtx_offset = (size_t)hmtx_off;
        loca_offset = (size_t)loca_off;
        glyf_offset = (size_t)glyf_off;

        build_hmtx_cache();
        parse_cmap((size_t)cmap_off);
        if (kern_off >= 0) parse_kern((size_t)kern_off);
        valid = true;
        return true;
    }

    // Pixel-height scale: px / (ascent - descent).
    float scale_for_pixel_height(float px) const {
        float h = (float)(ascent - descent);
        if (h <= 0.0f) h = (float)units_per_em;
        if (h <= 0.0f) h = 1.0f;
        return px / h;
    }

    // {ascent, descent, line_gap} in font units (hhea).
    void vmetrics(int& asc, int& desc, int& gap) const {
        asc = ascent; desc = descent; gap = line_gap;
    }

    // Scaled line height matching cov_atlas/stb convention:
    // (asc - desc + gap) * scale, clamped to >= px.
    float line_height_px(float px) const {
        float sc = scale_for_pixel_height(px);
        float lh = (float)(ascent - descent + line_gap) * sc;
        if (lh < px) lh = px;
        return lh;
    }
    float ascent_px(float px) const { return (float)ascent * scale_for_pixel_height(px); }
    float descent_px(float px) const { return (float)descent * scale_for_pixel_height(px); }

    uint32_t glyph_index(uint32_t cp) const {
        if (has_cmap12) {
            for (const auto& g : cmap12_groups) {
                if (cp >= g.start_char && cp <= g.end_char)
                    return g.start_glyph + (cp - g.start_char);
            }
        }
        if (cmap4.valid) return cmap4_glyph(cp);
        return 0;
    }

    HMetrics hmetrics(int gid) const {
        if (gid < 0 || gid >= num_glyphs || hmtx_cache.empty())
            return {units_per_em, 0};
        return hmtx_cache[gid];
    }

    float advance_px(int gid, float scale) const {
        return (float)hmetrics(gid).advance * scale;
    }

    int kern_advance(int g1, int g2) const {
        // binary search over file-ordered pairs (same as tables.lm)
        int lo = 0, hi = (int)kern_pairs.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            const auto& e = kern_pairs[mid];
            if (e.g1 == g1 && e.g2 == g2) return e.value;
            if (e.g1 < g1 || (e.g1 == g1 && e.g2 < g2)) lo = mid + 1;
            else hi = mid - 1;
        }
        return 0;
    }

    // Advance width of one decoded codepoint at `scale`, including kern vs
    // `prev_gid` (pass -1 for none). Mirrors sdf_atlas advance+kern math.
    float char_step(uint32_t cp, float scale, int& out_gid) const {
        out_gid = (int)glyph_index(cp);
        return advance_px(out_gid, scale);
    }

    // Rasterize one glyph to a coverage bitmap. `scale` = scale_for_pixel_height.
    // Returns false for empty/missing glyphs.
    bool rasterize_glyph(int gid, float scale, GlyphBitmap& out) const {
        out = GlyphBitmap();
        GlyphOutline outline;
        if (!parse_glyph(gid, outline, 0)) return false;
        if (outline.empty) return false;
        rasterize_outline(outline, scale, out);
        return out.width > 0 && out.height > 0;
    }

    // Convenience: decode-free codepoint rasterize.
    bool rasterize_codepoint(uint32_t cp, float scale, GlyphBitmap& out) const {
        return rasterize_glyph((int)glyph_index(cp), scale, out);
    }

private:
    // ---- big-endian readers (bounds-checked) ----
    uint16_t be16(size_t off) const {
        if (off + 2 > size) return 0;
        return (uint16_t)((data[off] << 8) | data[off + 1]);
    }
    int16_t be16s(size_t off) const { return (int16_t)be16(off); }
    uint32_t be32(size_t off) const {
        if (off + 4 > size) return 0;
        return ((uint32_t)data[off] << 24) | ((uint32_t)data[off+1] << 16) |
               ((uint32_t)data[off+2] << 8) | (uint32_t)data[off+3];
    }
    uint8_t be8(size_t off) const { return off < size ? data[off] : 0; }

    void build_hmtx_cache() {
        hmtx_cache.clear();
        if (hmtx_offset == 0 || num_glyphs <= 0 || num_h_metrics <= 0) return;
        hmtx_cache.reserve(num_glyphs);
        for (int i = 0; i < num_glyphs; ++i) {
            HMetrics m;
            if (i < num_h_metrics) {
                m.advance = be16(hmtx_offset + (size_t)i * 4);
                m.lsb = be16s(hmtx_offset + (size_t)i * 4 + 2);
            } else {
                m.advance = be16(hmtx_offset + (size_t)(num_h_metrics - 1) * 4);
                m.lsb = be16s(hmtx_offset + (size_t)num_h_metrics * 4 +
                              (size_t)(i - num_h_metrics) * 2);
            }
            hmtx_cache.push_back(m);
        }
    }

    uint32_t cmap4_glyph(uint32_t cp) const {
        if (cp > 0xFFFF) return 0;
        const CmapFormat4& c = cmap4;
        for (int i = 0; i < c.seg_count; ++i) {
            if (cp <= c.end_codes[i]) {
                if (cp < c.start_codes[i]) return 0;
                uint16_t ro = c.id_range_offsets[i];
                if (ro == 0) {
                    return (uint16_t)((cp + (uint32_t)(int32_t)c.id_deltas[i]) & 0xFFFF);
                }
                // glyphId = idRangeOffset[i] + 2*(cp - startCode[i]) measured
                // from the location of idRangeOffset[i] itself.
                size_t pos = c.id_range_offsets_base + (size_t)i * 2 + ro +
                             (size_t)(cp - c.start_codes[i]) * 2;
                uint32_t gid = be16(pos);
                if (gid != 0) gid = (gid + (uint32_t)(int32_t)c.id_deltas[i]) & 0xFFFF;
                return gid;
            }
        }
        return 0;
    }

    void parse_cmap(size_t off) {
        if (off + 4 > size) return;
        uint16_t num_sub = be16(off + 2);
        size_t fmt4_off = 0, fmt12_off = 0;
        bool have4 = false, have12 = false;
        for (int i = 0; i < num_sub; ++i) {
            size_t rec = off + 4 + (size_t)i * 8;
            if (rec + 8 > size) break;
            uint16_t platform = be16(rec);
            uint16_t encoding = be16(rec + 2);
            uint32_t sub_off = be32(rec + 4);
            size_t sub = off + sub_off;
            if (sub + 2 > size) continue;
            uint16_t format = be16(sub);
            if (format == 4 && !have4 &&
                (platform == 0 || (platform == 3 && (encoding == 1 || encoding == 0)))) {
                fmt4_off = sub; have4 = true;
            } else if (format == 12 && !have12 &&
                       (platform == 0 || (platform == 3 && encoding == 10))) {
                fmt12_off = sub; have12 = true;
            }
        }

        if (have4) {
            size_t p = fmt4_off;
            // format(2) length(2) language(2) segCountX2(2) ...
            int seg = be16(p + 6) / 2;
            cmap4.seg_count = seg;
            cmap4.end_codes.resize(seg);
            cmap4.start_codes.resize(seg);
            cmap4.id_deltas.resize(seg);
            cmap4.id_range_offsets.resize(seg);
            size_t q = p + 14; // skip format..rangeShift
            for (int i = 0; i < seg; ++i) cmap4.end_codes[i] = be16(q + i * 2);
            q += seg * 2 + 2; // reservedPad
            for (int i = 0; i < seg; ++i) cmap4.start_codes[i] = be16(q + i * 2);
            q += seg * 2;
            for (int i = 0; i < seg; ++i) cmap4.id_deltas[i] = be16s(q + i * 2);
            q += seg * 2;
            cmap4.id_range_offsets_base = q;
            for (int i = 0; i < seg; ++i) cmap4.id_range_offsets[i] = be16(q + i * 2);
            cmap4.valid = true;
        }

        if (have12) {
            size_t p = fmt12_off + 12;
            if (p + 4 <= size) {
                uint32_t n = be32(p);
                p += 4;
                if (p + (size_t)n * 12 <= size) {
                    for (uint32_t i = 0; i < n; ++i) {
                        CmapGroup g;
                        g.start_char = be32(p); g.end_char = be32(p + 4);
                        g.start_glyph = be32(p + 8);
                        cmap12_groups.push_back(g);
                        p += 12;
                    }
                    has_cmap12 = true;
                }
            }
        }
    }

    void parse_kern(size_t off) {
        if (off + 4 > size) return;
        uint16_t version = be16(off);
        (void)version;
        uint16_t n_tables = be16(off + 2);
        size_t p = off + 4;
        for (int t = 0; t < n_tables; ++t) {
            if (p + 6 > size) break;
            uint32_t sub_len = be32(p);
            uint16_t coverage = be16(p + 4);
            int format = (coverage >> 8) & 0xFF;
            bool horizontal = (coverage & 1) != 0;
            size_t sub_end = p + sub_len;
            if (format == 0 && horizontal && sub_len >= 14) {
                uint16_t n_pairs = be16(p + 6);
                size_t kp = p + 14;
                if (kp + (size_t)n_pairs * 6 <= size && kp + (size_t)n_pairs * 6 <= sub_end) {
                    for (int i = 0; i < n_pairs; ++i) {
                        KernEntry e;
                        e.g1 = be16(kp); e.g2 = be16(kp + 2);
                        e.value = be16s(kp + 4);
                        kern_pairs.push_back(e);
                        kp += 6;
                    }
                }
                return; // first horizontal format-0 subtable wins
            }
            if (sub_len == 0) break;
            p = sub_end;
        }
    }

    // ---- glyph parsing (glyph.lm port) ----

    bool parse_glyph(int gid, GlyphOutline& outline, int depth) const {
        outline = GlyphOutline();
        if (gid < 0 || gid >= num_glyphs || loca_offset == 0 || depth > 8) return false;

        size_t goff, glen;
        if (index_to_loc_format == 0) {
            size_t pos = loca_offset + (size_t)gid * 2;
            uint32_t s = be16(pos) * 2u;
            uint32_t e = be16(pos + 2) * 2u;
            if (e <= s) return false;
            goff = glyf_offset + s; glen = e - s;
        } else {
            size_t pos = loca_offset + (size_t)gid * 4;
            uint32_t s = be32(pos), e = be32(pos + 4);
            if (e <= s) return false;
            goff = glyf_offset + s; glen = e - s;
        }
        if (goff + glen > size || glen < 10) return false;

        size_t p = goff;
        int16_t num_contours = be16s(p);
        p += 10; // skip bbox too

        if (num_contours >= 0) {
            if (num_contours == 0) return true; // empty
            int ncont = num_contours;
            std::vector<uint16_t> end_pts(ncont);
            for (int i = 0; i < ncont; ++i) { end_pts[i] = be16(p); p += 2; }
            uint16_t instr_len = be16(p); p += 2 + instr_len;
            if (p > goff + glen) return false;

            // total points = last endPt + 1
            int num_points = (int)end_pts[ncont - 1] + 1;
            std::vector<uint8_t> flags;
            flags.reserve(num_points);
            while ((int)flags.size() < num_points && p < goff + glen) {
                uint8_t f = be8(p++);
                flags.push_back(f);
                if (f & 0x08) {
                    int rep = be8(p++);
                    for (int r = 0; r < rep && (int)flags.size() < num_points; ++r)
                        flags.push_back(f);
                }
            }
            if ((int)flags.size() < num_points) return false;

            std::vector<float> xs(num_points), ys(num_points);
            float cx = 0, cy = 0;
            for (int i = 0; i < num_points; ++i) {
                uint8_t f = flags[i];
                float dx = 0;
                if (f & 0x02) { // x short
                    dx = (float)be8(p++);
                    if (!(f & 0x10)) dx = -dx;
                } else if (!(f & 0x10)) {
                    dx = (float)be16s(p); p += 2;
                }
                cx += dx; xs[i] = cx;
            }
            for (int i = 0; i < num_points; ++i) {
                uint8_t f = flags[i];
                float dy = 0;
                if (f & 0x04) { // y short
                    dy = (float)be8(p++);
                    if (!(f & 0x20)) dy = -dy;
                } else if (!(f & 0x20)) {
                    dy = (float)be16s(p); p += 2;
                }
                cy += dy; ys[i] = cy;
            }

            int pt = 0;
            for (int c = 0; c < ncont; ++c) {
                int end_idx = end_pts[c];
                std::vector<FontPoint> contour;
                while (pt <= end_idx && pt < num_points) {
                    contour.push_back({xs[pt], ys[pt], (flags[pt] & 1) != 0});
                    ++pt;
                }
                if (!contour.empty()) outline.contours.push_back(std::move(contour));
            }
            outline.empty = outline.contours.empty();
            return true;
        }

        if (num_contours == -1) {
            // composite glyph
            bool more = true;
            int guard = 0;
            while (more && guard++ < 64) {
                if (p + 4 > goff + glen) break;
                uint16_t comp_flags = be16(p); p += 2;
                uint16_t sub_gid = be16(p); p += 2;
                float arg1, arg2;
                if (comp_flags & 0x01) {
                    arg1 = (float)be16s(p); arg2 = (float)be16s(p + 2); p += 4;
                } else {
                    arg1 = (float)(int8_t)be8(p); arg2 = (float)(int8_t)be8(p + 1); p += 2;
                }
                float sa = 1, sb = 0, sc = 0, sd = 1;
                if (comp_flags & 0x08) { // WE_HAVE_A_SCALE
                    sa = sd = be16s(p) / 16384.0f; p += 2;
                } else if (comp_flags & 0x40) { // X_AND_Y_SCALE
                    sa = be16s(p) / 16384.0f; sd = be16s(p + 2) / 16384.0f; p += 4;
                } else if (comp_flags & 0x80) { // TWO_BY_TWO
                    sa = be16s(p) / 16384.0f; sb = be16s(p + 2) / 16384.0f;
                    sc = be16s(p + 4) / 16384.0f; sd = be16s(p + 6) / 16384.0f; p += 8;
                }
                GlyphOutline sub;
                parse_glyph(sub_gid, sub, depth + 1);
                for (auto& cont : sub.contours) {
                    for (auto& pt : cont) {
                        float tx = sa * pt.x + sc * pt.y + arg1;
                        float ty = sb * pt.x + sd * pt.y + arg2;
                        pt.x = tx; pt.y = ty;
                    }
                    outline.contours.push_back(std::move(cont));
                }
                more = (comp_flags & 0x20) != 0;
            }
            outline.empty = outline.contours.empty();
            return !outline.empty;
        }
        return false;
    }

    // ---- outline flattening + rasterization (glyph.lm/rasterizer.lm port) ----

    void flatten_contour(const std::vector<FontPoint>& raw,
                         float sx, float sy,
                         std::vector<FontSegment>& segs) const {
        int count = (int)raw.size();
        if (count < 2) return;

        // Build working arrays with the same start-point fixup as glyph.lm.
        std::vector<FontPoint> pts;
        pts.reserve(count + 1);
        if (!raw[0].on_curve) {
            if (raw[count - 1].on_curve) {
                pts.push_back(raw[count - 1]);
                for (int i = 0; i < count - 1; ++i) pts.push_back(raw[i]);
            } else {
                pts.push_back({(raw[0].x + raw[count - 1].x) * 0.5f,
                               (raw[0].y + raw[count - 1].y) * 0.5f, true});
                for (int i = 0; i < count; ++i) pts.push_back(raw[i]);
            }
        } else {
            pts = raw;
        }

        int n = (int)pts.size();
        int i = 0;
        float cur_x = pts[0].x, cur_y = pts[0].y;
        const int STEPS = 4;
        while (i < n) {
            int next = (i + 1) % n;
            const FontPoint& p1 = pts[next];
            if (p1.on_curve) {
                segs.push_back({cur_x * sx, cur_y * sy, p1.x * sx, p1.y * sy});
                cur_x = p1.x; cur_y = p1.y;
                ++i;
            } else {
                int next2 = (i + 2) % n;
                const FontPoint& p2 = pts[next2];
                float end_x = p2.x, end_y = p2.y;
                if (!p2.on_curve) {
                    end_x = (p1.x + p2.x) * 0.5f;
                    end_y = (p1.y + p2.y) * 0.5f;
                    ++i;
                } else {
                    i += 2;
                }
                float prev_bx = cur_x, prev_by = cur_y;
                for (int step = 1; step <= STEPS; ++step) {
                    float t = (float)step / (float)STEPS;
                    float omt = 1.0f - t;
                    float bx = omt*omt*cur_x + 2.0f*omt*t*p1.x + t*t*end_x;
                    float by = omt*omt*cur_y + 2.0f*omt*t*p1.y + t*t*end_y;
                    segs.push_back({prev_bx * sx, prev_by * sy, bx * sx, by * sy});
                    prev_bx = bx; prev_by = by;
                }
                cur_x = end_x; cur_y = end_y;
            }
        }
    }

    void rasterize_outline(const GlyphOutline& outline, float scale,
                           GlyphBitmap& out) const {
        // Scale + invert Y (font y-up -> screen y-down), matching rasterizer.lm.
        std::vector<FontSegment> segs;
        segs.reserve(256);
        float min_x = 1e9f, max_x = -1e9f, min_y = 1e9f, max_y = -1e9f;
        for (const auto& cont : outline.contours) {
            size_t before = segs.size();
            flatten_contour(cont, scale, scale, segs);
            for (size_t k = before; k < segs.size(); ++k) {
                FontSegment s = segs[k];
                // negate y now so segments are in screen space
                s.y0 = -s.y0; s.y1 = -s.y1;
                segs[k] = s;
                min_x = std::min(min_x, std::min(s.x0, s.x1));
                max_x = std::max(max_x, std::max(s.x0, s.x1));
                min_y = std::min(min_y, std::min(s.y0, s.y1));
                max_y = std::max(max_y, std::max(s.y0, s.y1));
            }
        }
        if (segs.empty()) return;

        // floor for min, (int)(v + 0.999) for max — same as rasterizer.lm
        int i_min_x = (int)std::floor(min_x);
        int i_max_x = (int)(max_x + 0.999f);
        int i_min_y = (int)std::floor(min_y);
        int i_max_y = (int)(max_y + 0.999f);
        int w = i_max_x - i_min_x;
        int h = i_max_y - i_min_y;
        if (w <= 0 || h <= 0) {
            out.x_offset = i_min_x; out.y_offset = i_min_y;
            return;
        }

        out.width = w; out.height = h;
        out.x_offset = i_min_x; out.y_offset = i_min_y;
        out.pixels.assign((size_t)w * h, 0);

        // Scanline AA: SUB sub-rows per pixel row; within each sub-row the
        // x-extent of each inside span contributes its exact pixel overlap,
        // giving true horizontal+vertical antialiasing (stb 2x2 equivalent).
        const int SUB = 4;
        std::vector<std::pair<float,int>> inter;
        inter.reserve(64);
        for (int py = 0; py < h; ++py) {
            for (int sub = 0; sub < SUB; ++sub) {
                float sample_y = (float)(i_min_y + py) + ((float)sub + 0.5f) / (float)SUB;
                inter.clear();
                for (const auto& s : segs) {
                    bool crosses = (s.y0 <= sample_y && s.y1 > sample_y) ||
                                   (s.y1 <= sample_y && s.y0 > sample_y);
                    if (!crosses) continue;
                    float dy = s.y1 - s.y0;
                    if (dy == 0.0f) continue;
                    float ix = s.x0 + (sample_y - s.y0) * (s.x1 - s.x0) / dy;
                    inter.push_back({ix, s.y1 < s.y0 ? -1 : 1});
                }
                if (inter.size() < 2) continue;
                std::stable_sort(inter.begin(), inter.end(),
                                 [](const auto& a, const auto& b){ return a.first < b.first; });
                int winding = 0;
                bool inside = false;
                float span_x0 = 0.0f;
                for (size_t k = 0; k < inter.size(); ++k) {
                    int old_w = winding;
                    winding += inter[k].second;
                    bool now_inside = (winding != 0);
                    (void)old_w;
                    if (!inside && now_inside) {
                        inside = true; span_x0 = inter[k].first;
                    } else if (inside && !now_inside) {
                        inside = false;
                        float x0 = span_x0 - (float)i_min_x;
                        float x1 = inter[k].first - (float)i_min_x;
                        // pixels overlapped by [x0,x1)
                        int p0 = (int)std::floor(x0);
                        int p1 = (int)std::ceil(x1);
                        if (p0 < 0) p0 = 0;
                        if (p1 > w) p1 = w;
                        float wgt = 256.0f / (float)SUB; // per-sub-row max
                        for (int px = p0; px < p1; ++px) {
                            float ov = std::min(x1, (float)px + 1.0f) - std::max(x0, (float)px);
                            if (ov <= 0.0f) continue;
                            float add = ov * wgt;
                            float nv = (float)out.pixels[(size_t)py * w + px] + add;
                            out.pixels[(size_t)py * w + px] = nv > 255.0f ? 255 : (uint8_t)nv;
                        }
                    }
                }
            }
        }
    }
};

} // namespace LM::Runtime
