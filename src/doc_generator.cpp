#include "doc_generator.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/ast.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <map>
#include <vector>

namespace fs = std::filesystem;

namespace LM {

namespace {

std::string format_type(const std::shared_ptr<Frontend::AST::TypeAnnotation>& type) {
    if (!type) return "any";
    if (!type->typeName.empty()) {
        std::string res = type->typeName;
        if (type->isOptional) res += "?";
        return res;
    }
    if (type->isList && type->elementType) {
        return "[" + format_type(type->elementType) + "]";
    }
    if (type->isDict && type->keyType && type->valueType) {
        return "{" + format_type(type->keyType) + ": " + format_type(type->valueType) + "}";
    }
    if (type->isTuple) {
        std::string s = "(";
        for (size_t i = 0; i < type->tupleTypes.size(); ++i) {
            s += format_type(type->tupleTypes[i]);
            if (i + 1 < type->tupleTypes.size()) s += ", ";
        }
        return s + ")";
    }
    if (type->isUnion) {
        std::string s;
        for (size_t i = 0; i < type->unionTypes.size(); ++i) {
            s += format_type(type->unionTypes[i]);
            if (i + 1 < type->unionTypes.size()) s += " | ";
        }
        return s;
    }
    return "any";
}

struct DocCallout {
    std::string type; // "tip", "warning", "note", "caution", "deprecated"
    std::string title;
    std::string content;
};

struct DocParam {
    std::string name;
    std::string description;
};

struct DocExample {
    std::string title;
    std::string code;
};

struct ParsedDoc {
    std::string summary;
    std::vector<DocCallout> callouts;
    std::vector<DocParam> params;
    std::string return_desc;
    std::vector<DocExample> examples;
    std::vector<std::string> preconditions;
};

std::string trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

ParsedDoc parse_docstring(const std::string& raw) {
    ParsedDoc res;
    if (raw.empty()) return res;

    std::istringstream stream(raw);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }

    size_t i = 0;
    while (i < lines.size()) {
        std::string cur = trim(lines[i]);
        if (cur.empty()) {
            i++;
            continue;
        }

        // 1. GitHub style alerts: > [!WARNING], > [!NOTE], > [!TIP], > [!CAUTION]
        if (cur.rfind("> [!", 0) == 0) {
            std::string alert_tag;
            size_t end_bracket = cur.find(']');
            if (end_bracket != std::string::npos) {
                alert_tag = cur.substr(4, end_bracket - 4);
                std::transform(alert_tag.begin(), alert_tag.end(), alert_tag.begin(), ::tolower);
            }
            std::string content;
            i++;
            while (i < lines.size()) {
                std::string sub = trim(lines[i]);
                if (sub.rfind(">", 0) == 0) {
                    std::string c = trim(sub.substr(1));
                    if (!c.empty()) {
                        if (!content.empty()) content += " ";
                        content += c;
                    }
                    i++;
                } else {
                    break;
                }
            }
            std::string title = (alert_tag == "tip") ? "Idiomatic Usage & Best Practice" :
                                (alert_tag == "warning") ? "Warning" :
                                (alert_tag == "caution") ? "Caution" : "Note";
            res.callouts.push_back({alert_tag.empty() ? "note" : alert_tag, title, content});
            continue;
        }

        // 2. Doc tags: @tip, @warning, @note, @info, @caution, @deprecated
        if (cur.rfind("@tip", 0) == 0) {
            std::string c = trim(cur.substr(4));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                c += " " + n;
                i++;
            }
            res.callouts.push_back({"tip", "Idiomatic Usage & Best Practice", c});
            continue;
        }
        if (cur.rfind("@warning", 0) == 0) {
            std::string c = trim(cur.substr(8));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                c += " " + n;
                i++;
            }
            res.callouts.push_back({"warning", "Warning", c});
            continue;
        }
        if (cur.rfind("@caution", 0) == 0) {
            std::string c = trim(cur.substr(8));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                c += " " + n;
                i++;
            }
            res.callouts.push_back({"caution", "Caution", c});
            continue;
        }
        if (cur.rfind("@note", 0) == 0 || cur.rfind("@info", 0) == 0) {
            size_t off = (cur.rfind("@note", 0) == 0) ? 5 : 5;
            std::string c = trim(cur.substr(off));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                c += " " + n;
                i++;
            }
            res.callouts.push_back({"note", "Note", c});
            continue;
        }
        if (cur.rfind("@deprecated", 0) == 0) {
            std::string c = trim(cur.substr(11));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                c += " " + n;
                i++;
            }
            res.callouts.push_back({"deprecated", "Deprecated", c.empty() ? "This feature is deprecated and will be removed in a future release." : c});
            continue;
        }

        // 3. Parameters: @param <name> <description>
        if (cur.rfind("@param", 0) == 0) {
            std::string rest = trim(cur.substr(6));
            size_t space = rest.find_first_of(" \t");
            std::string pname, pdesc;
            if (space != std::string::npos) {
                pname = rest.substr(0, space);
                pdesc = trim(rest.substr(space));
            } else {
                pname = rest;
            }
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                if (!pdesc.empty()) pdesc += " ";
                pdesc += n;
                i++;
            }
            res.params.push_back({pname, pdesc});
            continue;
        }

        // 4. Return: @return or @returns
        if (cur.rfind("@return", 0) == 0) {
            size_t off = (cur.rfind("@returns", 0) == 0) ? 8 : 7;
            std::string r = trim(cur.substr(off));
            i++;
            while (i < lines.size()) {
                std::string n = trim(lines[i]);
                if (n.empty() || n[0] == '@' || n.rfind(">", 0) == 0 || n.rfind("```", 0) == 0) break;
                if (!r.empty()) r += " ";
                r += n;
                i++;
            }
            res.return_desc = r;
            continue;
        }

        // 5. Preconditions: @pre or @requires
        if (cur.rfind("@pre", 0) == 0 || cur.rfind("@requires", 0) == 0) {
            size_t off = (cur.rfind("@requires", 0) == 0) ? 9 : 4;
            res.preconditions.push_back(trim(cur.substr(off)));
            i++;
            continue;
        }

        // 6. Examples: @example or fenced ```lymar code block
        if (cur.rfind("@example", 0) == 0) {
            std::string ex_title = trim(cur.substr(8));
            if (ex_title.empty()) ex_title = "Idiomatic Usage";
            std::string code;
            i++;
            while (i < lines.size()) {
                std::string eline = lines[i];
                std::string etrim = trim(eline);
                if (!etrim.empty() && etrim[0] == '@') break;
                if (etrim.rfind("```", 0) == 0) {
                    i++;
                    continue;
                }
                code += eline + "\n";
                i++;
            }
            res.examples.push_back({ex_title, trim(code)});
            continue;
        }

        if (cur.rfind("```", 0) == 0) {
            std::string code;
            i++;
            while (i < lines.size()) {
                std::string eline = lines[i];
                if (trim(eline).rfind("```", 0) == 0) {
                    i++;
                    break;
                }
                code += eline + "\n";
                i++;
            }
            res.examples.push_back({"Idiomatic Usage", trim(code)});
            continue;
        }

        // Default: add to summary
        if (!res.summary.empty()) res.summary += "\n";
        res.summary += cur;
        i++;
    }

    return res;
}

struct DocItem {
    std::string kind; // "Function", "Frame", "Trait", "Type Alias", "Enum"
    std::string name;
    std::string visibility; // "pub", "prot", "private"
    std::string signature;
    std::string raw_doc;
    ParsedDoc parsed_doc;
    std::vector<std::string> traits;
    std::vector<std::pair<std::string, std::string>> members; // type, signature
};

std::string extract_doc_comment(const std::vector<std::string>& lines, int decl_line) {
    if (decl_line <= 1 || decl_line > static_cast<int>(lines.size())) return "";

    std::vector<std::string> comment_lines;
    int idx = decl_line - 2;

    while (idx >= 0) {
        std::string line = lines[idx];
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) {
            break;
        }
        std::string trimmed = line.substr(first);
        if (trimmed.rfind("///", 0) == 0) {
            std::string content = trimmed.substr(3);
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            comment_lines.push_back(content);
        } else if (trimmed.rfind("//", 0) == 0) {
            std::string content = trimmed.substr(2);
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            comment_lines.push_back(content);
        } else {
            break;
        }
        idx--;
    }

    std::reverse(comment_lines.begin(), comment_lines.end());
    std::string result;
    for (size_t i = 0; i < comment_lines.size(); ++i) {
        result += comment_lines[i];
        if (i + 1 < comment_lines.size()) result += "\n";
    }
    return result;
}

std::string extract_module_doc(const std::vector<std::string>& lines) {
    std::vector<std::string> comment_lines;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) {
            if (!comment_lines.empty()) break;
            continue;
        }
        std::string trimmed = line.substr(first);
        if (trimmed.rfind("//", 0) == 0) {
            size_t offset = (trimmed.rfind("///", 0) == 0) ? 3 : 2;
            std::string content = trimmed.substr(offset);
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            comment_lines.push_back(content);
        } else {
            break;
        }
    }

    std::string result;
    for (size_t i = 0; i < comment_lines.size(); ++i) {
        result += comment_lines[i];
        if (i + 1 < comment_lines.size()) result += "\n";
    }
    return result;
}

std::vector<DocItem> extract_items(const std::string& source, std::string& module_doc) {
    std::vector<std::string> lines;
    std::istringstream stream(source);
    std::string l;
    while (std::getline(stream, l)) {
        lines.push_back(l);
    }

    module_doc = extract_module_doc(lines);

    Frontend::Scanner scanner(source);
    scanner.scanTokens();
    Frontend::Parser parser(scanner);
    auto program = parser.parse();
    if (!program) return {};

    std::vector<DocItem> items;

    for (const auto& stmt : program->statements) {
        if (!stmt) continue;

        if (auto func = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
            DocItem item;
            item.kind = "Function";
            item.name = func->name;
            item.visibility = (func->visibility == Frontend::AST::VisibilityLevel::Public) ? "pub" : "private";
            item.raw_doc = extract_doc_comment(lines, func->line);
            item.parsed_doc = parse_docstring(item.raw_doc);

            std::string sig = (item.visibility == "pub" ? "pub fn " : "fn ") + func->name + "(";
            for (size_t i = 0; i < func->params.size(); ++i) {
                sig += func->params[i].first;
                if (func->params[i].second) {
                    sig += ": " + format_type(func->params[i].second);
                }
                if (i + 1 < func->params.size() || !func->optionalParams.empty()) sig += ", ";
            }
            for (size_t i = 0; i < func->optionalParams.size(); ++i) {
                sig += func->optionalParams[i].first;
                if (func->optionalParams[i].second.first) {
                    sig += ": " + format_type(func->optionalParams[i].second.first);
                }
                sig += " = ...";
                if (i + 1 < func->optionalParams.size()) sig += ", ";
            }
            sig += ")";
            if (func->returnType.has_value() && func->returnType.value()) {
                sig += ": " + format_type(func->returnType.value());
            }
            if (func->canFail) sig += "?";
            item.signature = sig;
            items.push_back(item);
            continue;
        }

        if (auto frame = std::dynamic_pointer_cast<Frontend::AST::FrameDeclaration>(stmt)) {
            DocItem item;
            item.kind = "Frame";
            item.name = frame->name;
            item.visibility = "pub";
            item.raw_doc = extract_doc_comment(lines, frame->line);
            item.parsed_doc = parse_docstring(item.raw_doc);
            item.traits = frame->implements;

            std::string sig = "frame " + frame->name;
            if (!frame->implements.empty()) {
                sig += ": ";
                for (size_t i = 0; i < frame->implements.size(); ++i) {
                    sig += frame->implements[i];
                    if (i + 1 < frame->implements.size()) sig += ", ";
                }
            }
            item.signature = sig;

            for (const auto& field : frame->fields) {
                if (!field) continue;
                std::string fvis = (field->visibility == Frontend::AST::VisibilityLevel::Public) ? "pub " : "";
                std::string ftype = field->type ? (": " + format_type(field->type)) : "";
                std::string desc = (field->isConst ? "val " : "var ") + fvis + field->name + ftype;
                item.members.push_back({"field", desc});
            }

            if (frame->init) {
                std::string isig = "pub init(";
                for (size_t i = 0; i < frame->init->parameters.size(); ++i) {
                    isig += frame->init->parameters[i].first;
                    if (frame->init->parameters[i].second) {
                        isig += ": " + format_type(frame->init->parameters[i].second);
                    }
                    if (i + 1 < frame->init->parameters.size()) isig += ", ";
                }
                isig += ")";
                item.members.push_back({"constructor", isig});
            }

            for (const auto& m : frame->methods) {
                if (!m) continue;
                std::string mvis = (m->visibility == Frontend::AST::VisibilityLevel::Public) ? "pub " : "";
                std::string msig = mvis + "fn " + m->name + "(";
                for (size_t i = 0; i < m->parameters.size(); ++i) {
                    msig += m->parameters[i].first;
                    if (m->parameters[i].second) {
                        msig += ": " + format_type(m->parameters[i].second);
                    }
                    if (i + 1 < m->parameters.size()) msig += ", ";
                }
                msig += ")";
                if (m->returnType) msig += ": " + format_type(m->returnType);
                item.members.push_back({"method", msig});
            }

            items.push_back(item);
            continue;
        }

        if (auto trait = std::dynamic_pointer_cast<Frontend::AST::TraitDeclaration>(stmt)) {
            DocItem item;
            item.kind = "Trait";
            item.name = trait->name;
            item.visibility = "pub";
            item.raw_doc = extract_doc_comment(lines, trait->line);
            item.parsed_doc = parse_docstring(item.raw_doc);
            item.signature = "trait " + trait->name;

            for (const auto& m : trait->methods) {
                if (!m) continue;
                std::string msig = "fn " + m->name + "(";
                for (size_t i = 0; i < m->params.size(); ++i) {
                    msig += m->params[i].first;
                    if (m->params[i].second) {
                        msig += ": " + format_type(m->params[i].second);
                    }
                    if (i + 1 < m->params.size()) msig += ", ";
                }
                msig += ")";
                if (m->returnType.has_value() && m->returnType.value()) {
                    msig += ": " + format_type(m->returnType.value());
                }
                item.members.push_back({"method requirement", msig});
            }

            items.push_back(item);
            continue;
        }

        if (auto type_decl = std::dynamic_pointer_cast<Frontend::AST::TypeDeclaration>(stmt)) {
            DocItem item;
            item.kind = "Type Alias";
            item.name = type_decl->name;
            item.visibility = "pub";
            item.raw_doc = extract_doc_comment(lines, type_decl->line);
            item.parsed_doc = parse_docstring(item.raw_doc);
            item.signature = "type " + type_decl->name + " = " + (type_decl->type ? format_type(type_decl->type) : "any");
            items.push_back(item);
            continue;
        }
    }

    return items;
}

} // namespace

std::string DocGenerator::generateMarkdown(const std::string& filepath, const std::string& source) {
    std::string module_doc;
    auto items = extract_items(source, module_doc);

    std::ostringstream out;
    out << "# API Documentation: `" << fs::path(filepath).filename().string() << "`\n\n";

    if (!module_doc.empty()) {
        out << "## Overview\n\n" << module_doc << "\n\n";
    }

    if (!items.empty()) {
        out << "## Symbols\n\n";
        for (const auto& it : items) {
            out << "- **" << it.kind << "**: [`" << it.name << "`](#" << it.name << ")\n";
        }
        out << "\n---\n\n";
    }

    for (const auto& it : items) {
        out << "### `" << it.name << "` <a id=\"" << it.name << "\"></a>\n\n";
        out << "**Kind**: " << it.kind << "  \n";
        out << "**Visibility**: `" << it.visibility << "`  \n\n";

        out << "```lymar\n" << it.signature << "\n```\n\n";

        if (!it.parsed_doc.summary.empty()) {
            out << it.parsed_doc.summary << "\n\n";
        }

        // Render Callouts in GitHub alert format
        for (const auto& c : it.parsed_doc.callouts) {
            std::string tag = c.type;
            std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
            out << "> [!" << tag << "]\n";
            if (!c.title.empty() && c.title != tag) {
                out << "> **" << c.title << "**: " << c.content << "\n\n";
            } else {
                out << "> " << c.content << "\n\n";
            }
        }

        // Render Preconditions
        if (!it.parsed_doc.preconditions.empty()) {
            out << "#### Preconditions (Contracts)\n\n";
            for (const auto& pre : it.parsed_doc.preconditions) {
                out << "- `requires " << pre << "`\n";
            }
            out << "\n";
        }

        // Render Parameters
        if (!it.parsed_doc.params.empty()) {
            out << "#### Parameters\n\n";
            out << "| Parameter | Description |\n";
            out << "| :--- | :--- |\n";
            for (const auto& p : it.parsed_doc.params) {
                out << "| `" << p.name << "` | " << (p.description.empty() ? "-" : p.description) << " |\n";
            }
            out << "\n";
        }

        // Render Return
        if (!it.parsed_doc.return_desc.empty()) {
            out << "#### Returns\n\n";
            out << it.parsed_doc.return_desc << "\n\n";
        }

        // Render Examples
        for (const auto& ex : it.parsed_doc.examples) {
            out << "#### Example: " << ex.title << "\n\n";
            out << "```lymar\n" << ex.code << "\n```\n\n";
        }

        // Render Members
        if (!it.members.empty()) {
            out << "#### Members\n\n";
            for (const auto& [type, desc] : it.members) {
                out << "- `" << desc << "` *(" << type << ")*\n";
            }
            out << "\n";
        }

        out << "---\n\n";
    }

    return out.str();
}

std::string DocGenerator::generateHTML(const std::string& filepath, const std::string& source) {
    std::string module_doc;
    auto items = extract_items(source, module_doc);

    std::string fname = fs::path(filepath).filename().string();
    std::ostringstream out;

    out << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
    out << "<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    out << "<title>" << fname << " - Lymar API Reference</title>\n";
    out << "<style>\n"
        << ":root {\n"
        << "  --bg-primary: #0a0e17;\n"
        << "  --bg-secondary: #111827;\n"
        << "  --bg-tertiary: #1f2937;\n"
        << "  --accent: #38bdf8;\n"
        << "  --accent-hover: #7dd3fc;\n"
        << "  --text-main: #f1f5f9;\n"
        << "  --text-muted: #94a3b8;\n"
        << "  --border-color: #334155;\n"
        << "}\n"
        << "* { box-sizing: border-box; }\n"
        << "body {\n"
        << "  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Inter', sans-serif;\n"
        << "  margin: 0; padding: 0; background: var(--bg-primary); color: var(--text-main); display: flex;\n"
        << "}\n"
        << "nav {\n"
        << "  width: 300px; height: 100vh; overflow-y: auto; background: var(--bg-secondary);\n"
        << "  border-right: 1px solid var(--border-color); padding: 24px 20px; position: fixed;\n"
        << "}\n"
        << "nav h2 { font-size: 1.15rem; color: var(--accent); margin-top: 0; margin-bottom: 16px; font-weight: 700; }\n"
        << "#search-input {\n"
        << "  width: 100%; padding: 8px 12px; background: var(--bg-tertiary); border: 1px solid var(--border-color);\n"
        << "  border-radius: 6px; color: #fff; font-size: 0.85rem; margin-bottom: 16px;\n"
        << "}\n"
        << "#search-input:focus { outline: none; border-color: var(--accent); }\n"
        << ".nav-link { display: block; color: var(--text-muted); text-decoration: none; padding: 6px 8px; font-size: 0.9rem; border-radius: 4px; }\n"
        << ".nav-link:hover { color: #fff; background: var(--bg-tertiary); }\n"
        << "main { margin-left: 300px; padding: 40px 48px; max-width: 950px; flex: 1; }\n"
        << "h1 { color: #fff; font-size: 2.2rem; margin-top: 0; padding-bottom: 16px; border-bottom: 1px solid var(--border-color); }\n"
        << "h2 { color: var(--accent); font-size: 1.4rem; margin-top: 36px; margin-bottom: 14px; }\n"
        << "h3 { color: #fff; font-size: 1.25rem; margin-top: 28px; margin-bottom: 12px; display: flex; align-items: center; gap: 10px; }\n"
        << "h4 { color: var(--accent); font-size: 1rem; margin-top: 20px; margin-bottom: 8px; text-transform: uppercase; letter-spacing: 0.05em; }\n"
        << ".badge { display: inline-block; padding: 3px 8px; border-radius: 4px; font-size: 0.75rem; font-weight: 600; text-transform: uppercase; }\n"
        << ".badge-pub { background: #064e3b; color: #6ee7b7; border: 1px solid #059669; }\n"
        << ".badge-private { background: #334155; color: #cbd5e1; }\n"
        << ".badge-type { background: #1e1b4b; color: #c7d2fe; border: 1px solid #4338ca; }\n"
        << ".code-sig { background: #090d16; border: 1px solid var(--border-color); padding: 14px 18px; border-radius: 8px; overflow-x: auto; font-family: 'Consolas', 'Fira Code', monospace; font-size: 0.95rem; color: #e2e8f0; }\n"
        << ".summary { color: #cbd5e1; line-height: 1.65; margin: 14px 0; font-size: 1rem; }\n"
        << "/* Callout styling */\n"
        << ".callout { margin: 16px 0; padding: 14px 18px; border-radius: 8px; border-left: 4px solid; font-size: 0.92rem; }\n"
        << ".callout-header { font-weight: 700; margin-bottom: 6px; display: flex; align-items: center; gap: 8px; }\n"
        << ".callout-tip { border-color: #10b981; background: rgba(16, 185, 129, 0.08); color: #d1fae5; }\n"
        << ".callout-tip .callout-header { color: #34d399; }\n"
        << ".callout-warning { border-color: #f59e0b; background: rgba(245, 158, 11, 0.08); color: #fef3c7; }\n"
        << ".callout-warning .callout-header { color: #fbbf24; }\n"
        << ".callout-note { border-color: #0284c7; background: rgba(2, 132, 199, 0.08); color: #e0f2fe; }\n"
        << ".callout-note .callout-header { color: #38bdf8; }\n"
        << ".callout-deprecated { border-color: #e11d48; background: rgba(225, 29, 72, 0.08); color: #ffe4e6; }\n"
        << ".callout-deprecated .callout-header { color: #fb7185; }\n"
        << "/* Example card */\n"
        << ".example-card { margin: 20px 0; border: 1px solid var(--border-color); border-radius: 8px; overflow: hidden; background: #080c14; }\n"
        << ".example-header { background: #162032; padding: 8px 16px; font-size: 0.82rem; font-weight: 700; color: #94a3b8; border-bottom: 1px solid var(--border-color); }\n"
        << ".example-card pre { margin: 0; padding: 14px 18px; overflow-x: auto; font-family: monospace; font-size: 0.92rem; color: #e2e8f0; }\n"
        << "/* Tables */\n"
        << "table { width: 100%; border-collapse: collapse; margin: 14px 0; font-size: 0.92rem; }\n"
        << "th { background: #162032; color: #94a3b8; text-align: left; padding: 10px 14px; font-weight: 600; border-bottom: 1px solid var(--border-color); }\n"
        << "td { padding: 10px 14px; border-bottom: 1px solid #1e293b; color: #cbd5e1; }\n"
        << "ul { padding-left: 20px; color: #cbd5e1; line-height: 1.6; }\n"
        << "hr { border: 0; border-top: 1px solid var(--border-color); margin: 36px 0; }\n"
        << "</style>\n"
        << "<script>\n"
        << "function filterNav() {\n"
        << "  var q = document.getElementById('search-input').value.toLowerCase();\n"
        << "  var links = document.querySelectorAll('.nav-link');\n"
        << "  links.forEach(function(l) {\n"
        << "    l.style.display = l.textContent.toLowerCase().includes(q) ? 'block' : 'none';\n"
        << "  });\n"
        << "}\n"
        << "</script>\n"
        << "</head>\n<body>\n";

    out << "<nav>\n<h2>" << fname << "</h2>\n";
    out << "<input type=\"text\" id=\"search-input\" placeholder=\"Filter symbols...\" oninput=\"filterNav()\">\n";
    out << "<div id=\"nav-list\">\n";
    for (const auto& it : items) {
        out << "<a class=\"nav-link\" href=\"#" << it.name << "\">" << it.name
            << " <span style=\"font-size: 0.75rem; opacity: 0.6;\">(" << it.kind << ")</span></a>\n";
    }
    out << "</div>\n</nav>\n";

    out << "<main>\n";
    out << "<h1>" << fname << " API Reference</h1>\n";

    if (!module_doc.empty()) {
        out << "<h2>Module Overview</h2>\n<div class=\"summary\"><p>" << module_doc << "</p></div>\n";
    }

    for (const auto& it : items) {
        out << "<div id=\"" << it.name << "\">\n";
        out << "<h3>" << it.name
            << " <span class=\"badge " << (it.visibility == "pub" ? "badge-pub" : "badge-private") << "\">" << it.kind << "</span>"
            << "</h3>\n";

        out << "<pre class=\"code-sig\"><code>" << it.signature << "</code></pre>\n";

        if (!it.parsed_doc.summary.empty()) {
            out << "<div class=\"summary\"><p>" << it.parsed_doc.summary << "</p></div>\n";
        }

        // Callouts
        for (const auto& c : it.parsed_doc.callouts) {
            std::string icon = (c.type == "tip") ? "💡" :
                               (c.type == "warning") ? "⚠️" :
                               (c.type == "caution") ? "🛑" :
                               (c.type == "deprecated") ? "🚫" : "ℹ️";
            out << "<div class=\"callout callout-" << c.type << "\">\n"
                << "<div class=\"callout-header\"><span>" << icon << "</span> " << c.title << "</div>\n"
                << "<div class=\"callout-content\"><p>" << c.content << "</p></div>\n"
                << "</div>\n";
        }

        // Preconditions
        if (!it.parsed_doc.preconditions.empty()) {
            out << "<h4>Contracts & Preconditions</h4>\n<ul>\n";
            for (const auto& pre : it.parsed_doc.preconditions) {
                out << "<li><code>requires " << pre << "</code></li>\n";
            }
            out << "</ul>\n";
        }

        // Parameters
        if (!it.parsed_doc.params.empty()) {
            out << "<h4>Parameters</h4>\n<table>\n<thead><tr><th>Parameter</th><th>Description</th></tr></thead>\n<tbody>\n";
            for (const auto& p : it.parsed_doc.params) {
                out << "<tr><td><code>" << p.name << "</code></td><td>" << p.description << "</td></tr>\n";
            }
            out << "</tbody>\n</table>\n";
        }

        // Returns
        if (!it.parsed_doc.return_desc.empty()) {
            out << "<h4>Returns</h4>\n<p style=\"color: #cbd5e1;\">" << it.parsed_doc.return_desc << "</p>\n";
        }

        // Examples
        for (const auto& ex : it.parsed_doc.examples) {
            out << "<div class=\"example-card\">\n"
                << "<div class=\"example-header\"><span>✨</span> Example: " << ex.title << "</div>\n"
                << "<pre><code>" << ex.code << "</code></pre>\n"
                << "</div>\n";
        }

        // Members
        if (!it.members.empty()) {
            out << "<h4>Members</h4>\n<ul>\n";
            for (const auto& [type, desc] : it.members) {
                out << "<li><code>" << desc << "</code> <em>(" << type << ")</em></li>\n";
            }
            out << "</ul>\n";
        }

        out << "</div><hr>\n";
    }

    out << "</main>\n</body>\n</html>\n";
    return out.str();
}

int DocGenerator::run(int argc, char** argv) {
    Options opts;
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--html") {
            opts.format = Format::HTML;
        } else if (arg == "--markdown") {
            opts.format = Format::Markdown;
        } else if (arg == "--stdout") {
            opts.stdout_only = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                opts.output_path = argv[++i];
            }
        } else if (arg[0] != '-') {
            opts.target_files.push_back(arg);
        }
    }

    if (opts.target_files.empty()) {
        std::cerr << "Error: No target input files or directories specified.\n";
        std::cerr << "Usage: lymar doc [--html|--markdown] [-o <output>] [--stdout] <file-or-dir>...\n";
        return 1;
    }

    std::vector<std::string> files;
    for (const auto& target : opts.target_files) {
        if (fs::is_directory(target)) {
            for (const auto& entry : fs::recursive_directory_iterator(target)) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    files.push_back(entry.path().generic_string());
                }
            }
        } else if (fs::is_regular_file(target)) {
            files.push_back(target);
        } else {
            std::cerr << "Warning: Target does not exist: " << target << "\n";
        }
    }

    if (files.empty()) {
        std::cerr << "Error: No .lm source files found to document.\n";
        return 1;
    }

    bool is_dir_output = !opts.output_path.empty() &&
        (fs::is_directory(opts.output_path) || (files.size() > 1 && opts.output_path.back() == '/'));

    if (is_dir_output && !fs::exists(opts.output_path)) {
        fs::create_directories(opts.output_path);
    }

    for (const auto& file : files) {
        std::ifstream in(file);
        if (!in.is_open()) {
            std::cerr << "Error: Failed to open file: " << file << "\n";
            continue;
        }
        std::stringstream buf;
        buf << in.rdbuf();
        std::string src = buf.str();

        std::string content = (opts.format == Format::HTML) ? generateHTML(file, src) : generateMarkdown(file, src);

        if (opts.stdout_only) {
            std::cout << content << "\n";
        } else if (is_dir_output) {
            std::string stem = fs::path(file).stem().string();
            std::string ext = (opts.format == Format::HTML) ? ".html" : ".md";
            fs::path out_file = fs::path(opts.output_path) / (stem + ext);
            std::ofstream out(out_file);
            out << content;
            std::cout << "Generated documentation: " << out_file.generic_string() << "\n";
        } else if (!opts.output_path.empty()) {
            fs::path p(opts.output_path);
            if (p.has_parent_path() && !fs::exists(p.parent_path())) {
                fs::create_directories(p.parent_path());
            }
            std::ofstream out(opts.output_path);
            out << content;
            std::cout << "Generated documentation: " << opts.output_path << "\n";
        } else {
            std::cout << content << "\n";
        }
    }

    return 0;
}

} // namespace LM
