# Lymar UI — Design Document

Status: implemented. `std.ui` is the retained, typed, component-oriented
application UI — the only app-UI system. `std.gui` remains the
immediate-mode game/debug/HUD layer; `std.game` remains the engine
runtime. The legacy "Fluent" widget monolith (`std.ui.components`,
`builder`, `layout`, `context` dispatch, `HitZone` hit-testing, and the
`std.app` Fluent entry points) has been removed; §1–§4 are kept as the
design rationale and migration record.

---

## 1. What exists today — honest inventory

### 1.1 `std.ui` — retained component system (current)

| Module | What it is |
|---|---|
| `component.lm` | `Component` trait contract (`measure`/`arrange`/`paint`/`on_event`), `Placed` embed, `TextBound`, geometry (`Size`/`Rect`) |
| `widgets/` | One file per widget — Button, TextInput, Checkbox, Toggle, Slider, Select, Calendar, ColorPicker, FileInput, Table, Chart, … (~30 widgets) |
| `container.lm` + `containers/` | `Flow`/`Container`/`ScrollView` plus `Stack`/`Grid`/`Mask`/`Overlay`/`Tooltip` |
| `tree.lm` | Frame driver: `update` (measure/arrange/paint), `submit` (replay), `dispatch` (hit-test/focus/scroll/overlays), repaint elision |
| `state.lm` | `Signal`/`ComputedSignal`/`Effect` reactive graph — the single state channel |
| `draw_list.lm` + `replay.lm` | Pooled GPU draw commands, zero per-frame alloc, clip stack |
| `event.lm` | `EventKind`/`EventResult`/`fire_action` widget-level semantics over `std.events` |
| `context.lm` | Shared plumbing only: `ui_init`, viewport size, dirty flag, UTF-8 helpers |
| `theme.lm` | `Palette` snapshot of `std.theme` tokens + elevation shadows |
| `index.lm` | Facade — `import std.ui as ui` |

**Historical note — the removed Fluent system**: the predecessor was a
`Fluent` trait monolith (`components.lm`, ~1,839 LOC, ~40 widgets) with a
string-keyed `ui_context` (`context.lm`), `builder.lm` constructors,
fixed-size `layout.lm`, `HitZone` parallel hit lists in `draw_list.lm`,
and `std.app.ui()/set_ui()/run(root)` entry points. It was retired once
the component set reached parity; all of it is deleted.

### 1.2 `std.gui` — immediate-mode GUI (~2,330 LOC, monolith)

One `GUI` frame with **~90 fields** of IMGUI state: cursor/flow layout,
columns, scroll offsets, popup/combo deferred state, style color/var
stacks, shadow/opacity/disabled modifier stacks, string-keyed
`windows`/`headers`/`scroll_offsets`/`editor_controllers` dicts, string
`hot_id`/`active_id` hit-testing, `IMGUIAnimationStore`.

**Strengths**: genuinely ImGui-grade feature coverage — `button`,
`checkbox`, `radio`, `toggle`, `slider`, `stepper`, `combo_box`,
`color_picker`, `plot_lines`, `plot_histogram`, `progress_bar`,
`input_text`, `input_text_multiline` (with real `EditorController`
integration: undo/redo/selection/cursor), windows, tabs, popups,
columns, same-line flow. Returns values directly (`button() -> bool`) —
the immediate ergonomics games want.
**Weaknesses**: string IDs everywhere (`make_id(label)` hash-keys state);
monolithic frame — every widget shares one state blob; string dicts for
per-widget persistence; the `get_style_var` color-stack bug class we hit
in `GUI.advance()`; no type safety on widget identity; per-frame
re-execution of the whole UI description.

### 1.3 `std.game` — engine layer, not a UI system

`Game` = window/timing/input/scenes (`std.scene` 2D `SceneManager`) +
`GUI` embed for IMGUI + `InputManager` (action/axis bindings) +
`Sprite`/`Texture2D`/`AnimatedSprite`/`ParticleEmitter2D`/`Camera2D`
helpers. After this session's refactor it consumes `std.events`
fan-out cleanly. **Verdict: it is a game *runtime*, and its UI story is
"embed std.gui" — which is correct for its niche.** It is not a third UI
system and shouldn't become one.

### 1.4 Shared infrastructure (post-refactor, working)

- `std.events` — typed OS events, `pump_events()` once/frame,
  `pending_events()` fan-out to any number of consumers.
- `std.app` — the single owner of window lifecycle, the event pump, and
  frame presentation. `App(title, w, h)` + `a.ui(root)` + `a.run()` for
  retained-UI apps; `a.open()`/`a.pump()`/`a.begin_pass()`/`a.end_pass()`/
  `a.close()` for custom loops (games). Event dispatch routes the
  `std.events` stream through `tree.dispatch`; `end_pass` runs
  `tree.update`/`submit` inside the gg pass with repaint elision.
- `std.gg` — immediate draw commands → sokol D3D11 / software fallback.
- `std.text` — `EditorController` (line/col editing, undo/redo,
  selection). `std.font` — supersampled glyph rasterizer.

## 2. Reference models — what each got right

### Flutter
Retained widget tree → layout pass → `RenderObject`s → retained `Layer`
tree replayed per frame. *Transfers*: the 3-pass structure and
"describe once, render many". *Costs*: GC'd heap, huge text stack
(LibTXT/HarfBuzz/ICU) we can't match.

### SwiftUI
Value-type view descriptions + diffing engine + property-wrapper state.
*Transfers*: declarative typed descriptions; state as first-class
bindings. *Costs*: result-builder DSL and value semantics Lymar lacks.

### Dear ImGui
Immediate calls + retained *data*. *Transfers*: the ergonomics are
right for tools/games — already proven by `std.gui`. *Costs*: string
IDs, `void*` lookups, no type safety — all fixable in Lymar.

### Qt Widgets
Retained `QObject` tree where **parents own children** — deterministic
deletion without GC; signals/slots; layouts as separate objects
(`QHBoxLayout`); stylesheets for theming; mature widget coverage;
model/view separation for big data.
*Transfers*: **parent-owned child lifetime maps directly onto Lymar's
region memory** — a subtree allocated in a parent's scope dies with it,
deterministically, no finalizers. Signals/slots ≈ our `Signal`/`Effect`
graph. Layout-objects ≈ layout-strategy components.

### QML / Qt Quick — the most relevant model, previously unanalyzed
- **Binding engine**: `width: parent.width / 2` — live property
  bindings re-evaluated on dependency change. *This is exactly our
  `ComputedSignal` graph* — QML proves the model works at product scale.
- **Retained scene graph → GPU batches**: Qt Quick renders the retained
  item tree through a scene-graph renderer into GL batches — UI quads as
  GPU vertex data. *This is our `DrawList` → `gg` → (future) d3
  vertex-stream path* — already architecturally aligned.
- **Declarative nesting**: `.qml` files are tree-shaped UI descriptions —
  maps onto our builder functions (`ui.column([ui.button(...)])`).
- **States/transitions**: explicit state machines on items — maps onto
  the dormant `lifecycle_state`/`active_transition` fields we just
  wired setters for.
- **ListView delegates**: model + delegate pattern — maps onto
  `[Component]` children + per-item widget factories.
*Costs*: QML's dynamic JS engine and runtime component loading —
Lymar's answer is **staged/compile-time** instead (see §4.6).

## 3. What Lymar actually has (fact-checked platform facts)

| Capability | Status |
|---|---|
| Region-based deterministic memory, no GC | Working — scope-bound cleanup, compiler-inferred lifetimes (`docs/guide.md`) |
| `frame` + `embed` zero-cost composition | Working — fields flatten, methods promote |
| `trait` contracts + dynamic dispatch | Working — `tests/oop/traits_dynamic.lm` |
| `staged fn` / `staged frame X(T: type)` | Working — **staged-time generics exist** (`std/ui/state.lm:62`) |
| `iter`, exhaustive `match` | Working |
| Fallible `T?`/`err()` | Working |
| First-class closures `fn(): nil` | Working |
| Reactive signals + effects | Partial — graph exists, adoption thin |
| Layout engine | Partial — fixed-size boxes, not constraints |
| Retained draw lists, zero per-frame alloc | Working |
| Typed fan-out events | Working — `std.events` |
| Font rasterizer + text editor | Working — per-glyph coverage; line/col editing only |
| `gpu.*` syntax | **Emulated only** — native lowering unverified |
| **No runtime generics** | `[Component]` trait-object trees are necessarily type-erased at the top level |
| **No GC** | Long-lived UI state must live in an owner (context/app state); per-frame scratch must be arena/reset — opposite strategies in one frame |
| **Ownership friction** | Module-level lists can't be `iter`ated by name; `var q = list` moves; `T | nil` needs `as` casts; `?` only on fallible types |
| **Register VM only** | No JIT; interpreter-bound per-widget work needs dirty-rect caching and batching from day one |
| **Text ceiling** | No BiDi, no complex-script shaping, no grapheme clusters, no IME |

## 4. The proposal: evolve `std.ui` in place

No `std.lui`, no third namespace — `std.ui` *becomes* the modern system.
`std.gui` stays for game debug overlays — correct niche, same
relationship as `std.game`/`std.app`. `std.game` stays an engine layer.
The duplication dies by convergence: one retained app-UI system.

### 4.1 Component model — traits + embed + parent-owned lifetime

```lymar
trait Component {
    fn measure(c: Constraints): Size;
    fn paint(d: DrawList, r: Rect): nil;
    fn on_event(e: events.Event): EventResult?;
}

frame Panel {
    embed Header;                    // zero-cost fixed structure
    pub children: [Component];       // dynamic children: trait objects
    pub id: WidgetId;                // int, per-context counter — kills string IDs
}
```

- **Parent-owned children** (Qt's best idea, free under regions): a
  `Panel`'s children are allocated in the panel's scope region — subtree
  teardown is deterministic, no GC, no `deleteLater`.
- `WidgetId` int replaces IMGUI's `make_id(label)` string hashing and
  Fluent's string keys — cheaper, type-safe, collision-free per context.
- Exhaustive `match (kind)` on `WidgetKind` keeps renderer/input
  dispatch compile-time checked.

### 4.2 Three passes per frame

```
process_events()     // std.events pump — once, fan-out to all consumers
layout pass          // measure/arrange — dirty subtrees only
paint pass           // into retained DrawList → gg replay
```

Flutter's architecture minus the weight. `std.ui.tree` implements it:
`update()` runs measure/arrange/paint, `submit()` replays the retained
draw list, `dispatch()` routes events — with repaint elision skipping
clean frames entirely.

### 4.3 Layout — QML/Flutter constraints, not fixed sizes

```lymar
frame Constraints { pub min_w: float; pub max_w: float;
                    pub min_h: float; pub max_h: float; }
```

- Two-phase `measure`/`arrange` like Flutter's `performLayout`.
- **Layout cache**: store last `Constraints`+`Rect` per component;
  re-layout only on constraint change or signal invalidation. On a
  register VM this is *the* perf lever — a 500-widget idle tree should
  cost ~0.
- `GridSpec`/breakpoints survive as opt-in layout-strategy components,
  not the universal model.

### 4.4 State — QML bindings expressed as typed signals

QML's binding engine is the right idea with the wrong implementation
(dynamically-typed JS expressions). Lymar's version:

```lymar
var count = ui.signal(0);
ui.label("").bind_text(count.map(ui.show_count));  // ComputedSignal[str]
```

- Typed signal kinds (`StrSignal` etc.) — extend the set, never `any`.
- `Effect` cleanup binds to the widget's region scope — deterministic
  teardown GC frameworks can't match (Qt needed `destroy()` calls;
  we get it from scope exit).
- **`staged` static subtrees**: `staged fn build_login(): ComponentTree`
  folds whole static screens at compile time — QML loads .qml at
  runtime; we compile it away. This is the biggest Lymar-only win.

### 4.5 Events — `std.events` fan-out, int IDs

UI is one consumer of `pending_events()`; hit-testing reads layout-pass
rects (no string-hash hit map); `on_event -> EventResult?` gives
explicit bubbling; text input routes through `std.text.EditorController`
on the focused component — reuse, don't rewrite.

### 4.6 Where Lymar pulls ahead

1. **`staged` UI** — compile-time-folded static screens; no equivalent
   in Flutter/SwiftUI/QML.
2. **Region-scoped effects** — deterministic reactive cleanup.
3. **Exhaustive `match` dispatch** — renderer/input switches are
   compile-time checked.
4. **`trait Component` contracts** — missing `measure`/`paint`/`on_event`
   is a compile error, not a runtime nil (the `GUI.advance` bug class).
5. **`embed` composites** — Panel=header+body+footer flattens to zero
   overhead; QML needs separate `Item` wrappers.
6. **GPU paint path later** — UI quads/text are ideal vertex-stream
   content; the d3 pipeline proves it. Blocked on native lowering —
   CPU draw lists are the oracle until then.

### 4.7 Where Lymar loses — design around it honestly

1. **Text** — no BiDi/shaping/IME/graphemes. v1: LTR, codepoint editing
   via `EditorController`. Document the ceiling; it's a `std.text`
   problem UI inherits.
2. **Type erasure** — `[Component]` trait objects mean indirect calls.
   Mitigate: `WidgetKind` enum dispatch, retained (not rebuilt) widgets,
   draw-list batching.
3. **Register-VM throughput** — budget dirty-rect layout + batched
   paint + lazy signal propagation from day one.
4. **Ownership rules become API law** — never return module list
   bindings (return copies); no `T | nil` in hot widget fields; `val`
   over `var`; typed signal callbacks, never `any`.
5. **No generics** — accept `[Component]`; builders hide it.

### 4.8 What dies / what stays

| System | Verdict |
|---|---|
| `std.ui` component tree (`component`/`widgets`/`containers`/`tree`/`state`/`draw_list`) | **Done** — the system described in §4–§5 is the implementation; the Fluent predecessor is deleted |
| `std.gui` IMGUI | **Keep** — game/debug niche; already complements `std.game` |
| `std.game` | **Keep** — engine layer; UI story stays "embed std.gui" |
| `std.app` | **Keep** — sole owner of window + event pump + present; drives both retained UI (`a.ui`) and games (`a.game`-style manual loop / `on_update`/`on_draw` hooks) |
| `std.events`, `std.text`, `std.font`, `std.theme` | **Keep** — shared infrastructure the UI builds on |
| String widget IDs, `any` callbacks, `UIEvent` duplication, Fluent widgets/`HitZone`s/`ui_context` dispatch | **Deleted** — `WidgetId` ints, typed signals, `std.events` types, `Component` contracts |

## 5. Milestones

1. **M1 Skeleton** — ✅ `trait Component` + `Size`/`Rect` geometry +
   `Placed` embed + paint into `DrawList`; `Label` end-to-end with pixel
   verification (`tests/ui_component_skeleton.lm`).
2. **M2 Core set** — ✅ Button, TextInput (`EditorController`),
   Flow/Container/ScrollView, `tree.lm` focus + frame driver; real
   `std.events` routing, hit-testing, scroll, on_change/on_scroll/
   on_arrange callbacks (`tests/ui_widgets.lm`).

### Compiler semantics discovered during M1/M2 (design constraints)

- **Trait-object dispatch cannot take managed (frame) arguments** —
  `paint(d: DrawList)`, `on_event(e: Event)`, `measure(c: Constraints)`
  all fail the ownership checker ("opaque callable has no proven
  ownership contract"). Managed *returns* are fine. → Trait signatures
  use scalar/enum args only; `paint()` emits into the shared
  `dl.paint_ctx` draw list owned by `std.ui.tree`.
- **Frame→trait coercion snapshots the frame** — after `parent.add(child)`,
  the concrete var is stale; the live widget exists only inside the tree.
  → Widget state is observed through **signals** (`text_sig`,
  `scroll_sig`, bound `StrSignal`s) and the live `rect` alias, not field
  reads or one-shot callbacks.
- **`mixin` shadowing — FIXED**: mixin members used to shadow host
  members; injection now dedups fields and methods so the host wins,
  matching `embed`. `frame Placed` stays an `embed` (host `arrange`
  wins for containers either way).
- **`embed` does not run `init()`** — `Placed` fields carry defaults.
- Module-level `[T]` bindings can't be `iter`ated by name or moved;
  frame args to `pub fn`s move on assignment (use callbacks/module vars
  for shared mutable test state).
- **Frame→trait snapshots SHARE frame-typed fields** — sub-objects
  (signals, `EditorController`, `Rect`) are references; only the top-level
  struct is copied. `var r = widget.rect` taken before `add()` is a live
  alias *if* arrange mutates in place (never rebinds `self.rect`).
- **Module `pub var`s are read-only from other modules** (writes
  rejected at compile time) — mutable module state changes through
  `pub fn` setters only.
- **Module-qualified fn values — FIXED**: `mod.fn` used as a value used
  to lower to `LoadGlobal`, but functions are never stored in globals_,
  so the value was always nil (silent no-op calls). Now lowers to a
  callable name reference; show-imported bare names (`import m show f`)
  resolve to their qualified symbol too. Module *variables* of fn type
  still load from globals correctly.
- **Closures captured module-level vars by value — FIXED**: a lambda
  reading a module var snapshotted it at creation, so `g = g + 1`
  inside a closure silently operated on a stale copy. Module bindings
  (root scope, no parent) are now excluded from capture and resolve
  through globals. Local captures are unchanged (still by value).
- **Union-typed fn vars — FIXED**: the nil coercion was the same
  LoadGlobal bug, not a union problem. `(fn(): nil)?` bindings now hold
  module fns, show-imported fns, and locals correctly.
- **`T?` on trait objects ok-wraps — WORKAROUND**: a method or function
  returning `Component?` wraps the trait object in the fallible `ok(...)`
  frame, and `as Component` does not unwrap it — later trait dispatch
  fails with `unresolved function __lir_internal_ok__.<method>`. `T | nil`
  returns don't coerce Frame→Union either. → Optional-trait channels use
  `any` (`child_at`, `find_widget`); cast back with `as Component`.
- **Implicit Frame→Trait coercion ignores trait default methods** —
  `is_type_compatible` requires every trait method name present in the
  frame's own method list. → Shared leaf behavior lives on `Placed`
  (promoted via `embed`), not as trait defaults.
- **Staged fns fold intra-module only** — a cross-module staged call
  yields `nil` at runtime. → staged helpers use the d3 pattern:
  private `staged fn` + `pub const` pre-folds + `pub fn` runtime twins.
  The stage-0 folder also rejects parenthesized subexpressions in return
  position — write left-associative chains.

3. **M3 Reactivity** — ✅ `TextBound` embed (`text` + `text_sig:
   StrSignal` + `string_val()`/`bind_text()`) on Label/Button;
   `TextInput.text_sig` always present, two-way `sig ↔ EditorController`
   reconcile each paint; `ScrollView.scroll_sig: FloatSignal` two-way;
   `tree.dirty` flag + `enable_reactive()` wired to
   `state.register_dirty_notifier`. `tests/ui_widgets.lm` verifies
   signal→repaint, edit→signal, external set→reconcile, wheel→signal,
   external scroll→arrange. `tests/ui_reactive.lm` completes the graph:
   `subscribe` callbacks, `Effect` run/re-run/cleanup/dispose lifecycle,
   `batch_updates` dirty coalescing, `ComputedStr` derivation, and a
   computed→signal→widget repaint chain. `on_change`/`on_scroll`/
   `on_arrange` callbacks deleted — signals are the single state channel.
4. **M4 `staged` static trees + WidgetId — ✅** `Placed.id` assigned by
   `component.next_widget_id()` in every widget `init` (unique, nonzero,
   immutable post-snapshot); `widget_id()` promoted through `embed`
   satisfies the trait; `child_count()`/`child_at(i): any` on `Placed`
   (leaf defaults) overridden by Flow/Container/ScrollView enable
   `tree.find_widget(root, id): any` depth-first lookup. Staged side:
   `breakpoint_cols`/`folded_text_width` helpers (private staged fold →
   `pub const` breakpoints + `pub fn` runtime twins; the module was
   retired with the Fluent cleanup). `tests/ui_m4_static.lm` built a
   static screen whose column count was staged-derived and verified id
   uniqueness, nested lookup, post-update stability, and that
   `Label.measure` agreed with the folded text-width heuristic.
5. **M5 Perf pass — ✅** Repaint elision: `enable_reactive()` now enables
   `tree.repaint_elision`; `update()` skips arrange+paint when `dirty == 0`
   and the viewport is unchanged, while `submit()` replays the retained
   draw list. Dirty sources: signal `set()` via the registered notifier,
   `dispatch()` on `Handled` results, `request_repaint()`, and any
   viewport resize. Audit counters `repainted_frames`/`skipped_frames`
   expose the hit rate. Batching audit: `dl.dl_clip_balance()` verifies
   clip push/pop balance; replay remains a single `gg.begin/end_batch`.
   Alloc profiling: `dl_alloc_cmd` slot reuse means `len(cmds)` is
   stable across identical frames — `tests/ui_m5_perf.lm` asserts no
   growth over 30 clean frames plus identical `cmd_count`. Partial
   dirty-RECT damage (repaint only changed regions) is deferred to M7 —
   it needs GPU-side scissor damage, not just draw-list bookkeeping.
6. **M6 Text honesty — ✅** `std.text` gained three modules:
   `utf8.lm` (codepoint decode/encode — std.string is byte-indexed),
   `bidi.lm` (UBA subset: bidi classes, paragraph direction, implicit
   levels, L2 visual reorder for the LTR renderer), `shaping.lm`
   (lam-alef mandatory ligatures U+FEF5–FEFC, Hebrew sofit finals).
   `prepare_display(text)` = shape→visual-order with an ASCII fast
   path; Label/Button/TextInput paint through it and Label.measure
   measures the display string. Explicit limits (in module headers):
   no bracket mirroring, no mark positioning, no full Arabic contextual
   table (engine skeleton present, per-letter table deferred), neutrals
   resolve by paragraph direction, single-paragraph scope, and glyph
   coverage depends on the loaded font's cmap. `tests/text_bidi_shaping.lm`
   covers roundtrip, levels, visual order, ligatures, sofit, and the
   widget emit path. Completion pass added `grapheme.lm` (cluster
   boundaries — EditorController move/backspace/delete_char were
   byte-granular and could split UTF-8 sequences; now cluster-safe),
   `layout.lm` (`char_count`/`measure_width`/`wrap_text`/`wrap_width`,
   codepoint units, space-preferring greedy wrap), real `selection_text()`
   (was copy-everything stub) and `delete_char()`. Font metric accuracy:
   `std/ui/text_metrics.lm` loads the system font once via
   `std.image.font` (same stb_truetype family as the renderer) and
   serves cached `text_width`/`line_height` in real advances; Label/
   Button/TextInput measure and center with it. Fallback is the staged
   8px heuristic when no font is available. `tests/
   text_unicode_editing.lm` covers boundaries, multibyte editing,
   cross-line selection, and wrapping.
   Metric parity (final fix): when a graphics context is live,
   `text_metrics` defers to `gg.measure_text`/`gg.get_line_height` —
   the renderer's own fons metrics context, same embedded font and
   same `font_scale >= 1.5 -> scale 2` mapping `replay()` uses, so
   measured widths are pixel-exact with what is drawn. Headless or
   contextless runs fall back to `std.image.font` system metrics at
   the renderer-mapped size (13px/20px), then the staged 8px
   heuristic.
7. **M7 GPU paint** *(blocked on native lowering)* — UI quads through
   the d3 vertex-stream pipeline.

### Convergence updates (post-M6)

The §4 end-state is now partially real:

- **`std.ui` facade** — `import std.ui as ui` is the single surface:
  `Component`/`Placed`/`TextBound`/`Size`/`Rect`, all widgets,
  containers, typed signals, and the tree driver. Mutable tree audit vars
  (`dirty`, `repaint_elision`, counters) are intentionally not re-exported
  — `pub import show` of a `pub var` captures a value snapshot, not a live
  alias; read them via `std.ui.tree` directly.
- **`std.app` integration** — `a.ui(root)` installs a `Component` tree;
  `App.step`/`present` pump `std.events` once per frame, route the stream
  through `tree.dispatch`, and run `tree.update`/`submit` inside the gg
  pass with repaint elision. Games plug in via `Game.attach()` (module-fn
  hooks) or the manual `a.pump()`/`a.begin_pass()`/`a.end_pass()` loop —
  `std.game` no longer touches windowing or the GPU pass.
- **Widget coverage** — the full legacy Fluent widget set is ported:
  Label, Button, TextInput, Checkbox, Toggle, Slider, ProgressBar,
  Link, Spacer, Badge, Alert/Toast, Stat, Indicator, Steps, Timeline,
  Diff, Image, ColorPicker, Calendar, FileInput, Card, Accordion,
  FormField, TreeNode, Tabs, Select/MultiSelect, Stepper, RangeSlider,
  Filter, Table, and Chart (bar/line/pie + plot aliases)
  (`tests/ui_more_widgets.lm`). Container children are typed
  `[Component]`; constructor-facing child params take `any` because the
  type checker does not coerce frame lists/optionals into trait
  collections — widgets cast once at the boundary.
- **Widget file layout** — `std.ui.widgets` is a directory module:
  `std/ui/widgets/*.lm` each hold one widget, and `index.lm` re-exports
  them through the unchanged `std.ui.widgets` / `std.ui` facade.
- **Structural containers** — `std.ui.containers` (`std/ui/containers/`)
  ports the remaining legacy container kinds as real `Component`s:
  `stack` (all children share the full rect), `grid` (fixed-column
  row-major layout), `mask` (child clipped via draw-list
  `ClipPush`/`ClipPop`; `shape` is stored for API parity but clipping is
  currently rectangular), `overlay` (single child at an absolute
  offset), and `tooltip` (hover bubble). `row`/`column`/`scroll_view`
  stay in `std.ui.container`; legacy `join` is just a horizontal
  container (= `row`). `Flow` (row/column) distributes leftover
  main-axis space to children with `expand > 0` proportionally to
  their weight — `Stat` and `Chart` ship with `expand = 1.0`, so cards
  fill their row/column; set `widget.expand` to opt other widgets in.
- **Theming** — `std.ui.theme.palette()` snapshots
  `std.ui.theme.global_theme` (ColorPalette + Spacing/Typography/Shape
  tokens) into a flat `Palette` at widget `init` time; widget color
  fields default from it and remain per-instance overridable. Derived
  shades (`surface_hover`, `track`, `on_accent`, `selection`,
  `text_disabled`, …) are lerped from the base palette. Recolor by
  mutating `global_theme` before constructing widgets — there is no
  live re-theme of retained instances yet.
- **Hover propagation** — `MouseMove` bypasses the per-child bounds
  gate in `Flow`/`Stack`/`Grid`/`ScrollView` and the single-child
  containers so hover widgets see the pointer leave and clear state;
  press/key events remain bounds-gated.
- **Overlay channel** — `tree.push_overlay`/`remove_overlay` gives
  transient popups (Select dropdowns) paint-on-top and first-chance
  pointer dispatch past their laid-out siblings; Select expands its
  arranged bounds while open so the menu region is hit-testable.
- **`UIEvent` deleted** — the string-keyed `UIEvent` frame, its
  constructors, and `dispatch_event` are gone from `std.ui.event`
  (`EventKind`/`EventResult`/`fire_action` remain).
- **Legacy Fluent removed** — the `Fluent` trait monolith
  (`components.lm`), `builder.lm`, `layout.lm`, `forms`/`navigation`/
  `charts`/`dialog`/`grid`/`window`/`application`/`theme`/`staged`,
  the `ui_context` Fluent dispatch in `context.lm`, `HitZone` hit
  lists in `draw_list.lm`, and the `std.app.ui()/set_ui()/run(root)`
  entry points are all deleted. `context.lm` survives only as shared
  plumbing (`ui_init`, viewport size, dirty flag, UTF-8 helpers);
  `draw_list.lm` carries draw commands only — hit-testing lives in
  `std.ui.tree`. All v1 tests were removed; the `ui_*` suite is the
  coverage.

## 6. The pitch

Flutter: "everything is a widget" on a GC'd heap.
SwiftUI: "declarative, diffed, typed" on value semantics.
QML: "bindings + scene graph" on a JS engine.
**Lymar: compile-time-verified component contracts, zero-cost embedded
composition, deterministic region memory, staged compile-time UI, and
exhaustive enum dispatch — on a register VM that forces you to respect
the frame budget.** The UI that wins here isn't the one with the most
widgets; it's the one where the compiler catches what Flutter finds at
runtime, and where `staged` does what no GC'd framework can.
