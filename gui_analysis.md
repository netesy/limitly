# GUI Architecture Analysis and Integration Report

## 1. Overview
The Limitly standard library offers two distinct User Interface paradigms:
- **`std.ui`**: A retained-mode, declarative Flexbox-based UI framework.
- **`std.game.gui`**: An immediate-mode GUI framework designed for per-frame execution.

Both libraries initially lacked advanced multi-line text editing, granular focus management, and clipboard integration capabilities out-of-the-box. This report details the architectural improvements applied to make both libraries production-ready, achieving feature parity and maintaining decoupling.

## 2. Shared Subsystem Architecture (`std.text` & `std.focus`)
To avoid duplicating complex text rendering and cursor manipulation logic, a decoupled `std.text` module was introduced:
- **`std.text.document.TextDocument`**: Handles string manipulation, line breaks, insertions, and deletions with an efficient line-based backing array.
- **`std.text.cursor.Cursor` & `Selection`**: Manages cursor positioning and text selection logic.
- **`std.text.controller.EditorController`**: Orchestrates operations, provides history for Undo/Redo operations, and maintains a bridge to external environments (via function delegates for clipboard integration).

Additionally, **`std.focus.manager.FocusManager`** was created to act as a centralized state machine dictating the active input target, solving focus overlapping problems across multiple input fields.

## 3. Integration Challenges & Resolutions
### Complexity Faced: The Cyclic Dependency Problem
Limitly enforces strict file-level import cycles.
* **Problem:** Integrating keyboard polling (`get_modifier_state()`) and clipboard state (`get_clipboard_string()`) from `std.app` directly into `std.ui.context` or `std.game.gui` resulted in fatal circular dependency errors (because `std.app` imports the UI systems to proxy inputs).
* **Resolution via Composition and Delegates:** Instead of statically importing `std.app`, focus state and modifier states are driven structurally. The UI pipelines simply ingest the keycodes, and the application layer forwards the OS clipboard callbacks dynamically (via closures) into `EditorController` during input consumption. Focus Management was also built via composition (putting `FocusManager` instances into `GUI` and `UIContext` structs) rather than relying on global singletons that trigger module cycles.

## 4. Evaluation and Comparison to Industry Standards
* **Retained Mode (`std.ui`)**: Similar to React/SwiftUI, but requires explicit layout triggers. The new `text_area` widget dynamically captures text editor state across frames via the `text_editor_state` persistent payload in the `Widget` struct, solving the "retained-mode local state" problem commonly faced in early frameworks.
* **Immediate Mode (`std.game.gui`)**: Similar to Dear ImGui. The `input_text_multiline` function maps an ID to a persistent `EditorController` stored in `self.editor_controllers` dict, allowing it to preserve undo/redo history and cursor positions across continuous `[frame 0, frame 1, ...]` execution sequences.
* **Industry Standard Benchmarking**: The new implementations align well with standard decoupling architectures seen in Flutter and Qt (where the text painting is separated from the logical text controller). It features full multi-line text input, keyboard navigation (arrow keys), Undo/Redo buffers (Ctrl+Z, Ctrl+Y), and Backspace handling natively.

## 5. Conclusion and Improvements
The newly added widgets make Limitly a complete UI solution.
**Future Improvements Needed**:
- Native Unicode/UTF-8 byte offset tracking (currently simple char splitting is used as a mock boundary).
- Scrollbar integration when the number of lines exceeds the visible `h` height block.
- Text selection rendering over regions (currently only cursor `|` line is actively highlighted).
