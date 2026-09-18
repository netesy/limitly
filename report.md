# Comprehensive Architectural Analysis & Hardened Unified Subsystems Report
**Limit UI Framework (`std.ui`), Immediate-Mode Game GUI (`std.game.gui`), Shared Shadow Model, & Unified Animation Subsystem (`std.animation`)**

---

## Executive Summary

Limit features a dual-paradigm GUI architecture built around a single shared core:
1. **`std.ui`**: A retained-mode, fluent, declarative UI framework designed for applications, desktop tools, and cloud consoles (`gui_showcase.lm`).
2. **`std.game.gui`**: An immediate-mode (IMGUI), zero-DOM procedural engine optimized for games, HUD overlays, tools, and real-time interactive scenes (`game_showcase.lm`).

This report documents the architectural audit and hardening pass over Limit's visual property model, first-class shared `Shadow` type, rendering pipeline, widget transition lifecycle, accessibility preferences, and unified animation core (`std.animation`).

---

## Part 1: Shared Core Architectural Invariant

The animation, style, and graphics pipeline preserves this architectural invariant across both retained and immediate paradigms:

```
                    SHARED CORE
                         │
                 ┌───────┴────────┐
                 │                │
              std.ui        std.game.gui
          (Retained Mode)   (Immediate Mode)
                 │                │
                 └───────┬────────┘
                         │
                  std.animation
                         │
        ┌────────────────┼────────────────┐
        │                │                │
     Timing           Property         Physics
  (Easing/Keys)      Animation         (Spring)
        │                │                │
        └────────────────┼────────────────┘
                         │
                    Style/State
                         │
              ┌──────────┼──────────┐
              │          │          │
            Layout      Paint    Composite
              │          │          │
              └──────────┼──────────┘
                         │
                       std.gg
```

### Architectural Guarantees
* **Single Animation Implementation**: A shared `PropertyAnimation`, `Spring`, and `Easing` engine powers both paradigms.
* **Single Shadow Type**: A single `Shadow` frame in `std/graphics/shadow.lm` is consumed by both `std.ui` and `std.game.gui`.
* **Zero-DOM Preservation**: The immediate-mode engine remains immediate-mode and does not allocate a permanent DOM or widget tree.
* **Declarative Fluent Preservation**: Retained UI widgets retain method-chained declarative modifiers (`.animate()`, `.spring()`, `.shadow()`, `.enter()`, `.exit()`).

---

## Part 2: Animatable Property Model & Capability Matrix

| Visual Property | Animatable? | Requires Layout Pass? | Requires Repaint? | Compositor / Layer Pass |
| :--- | :--- | :--- | :--- | :--- |
| **opacity** | Yes | ❌ No | Yes | Layer Opacity Pass |
| **color** / **background_color** | Yes | ❌ No | Yes | Paint Pass |
| **foreground_color** / **border_color**| Yes | ❌ No | Yes | Paint Pass |
| **width** / **height** | Yes | Yes | Yes | Layout + Paint Pass |
| **min_width** / **max_width** / **min_height** / **max_height** | Yes | Yes | Yes | Layout Pass |
| **padding** / **margin** / **gap** / **spacing** | Yes | Yes | Yes | Layout Pass |
| **position (x, y)** | Yes | Yes | Yes | Layout / Translate Pass |
| **translation** / **scale** / **rotation** | Yes | ❌ No | Yes | Composite / Layer Pass |
| **border_width** / **corner_radius** | Yes | Yes (if sizing) | Yes | Paint Pass |
| **shadow (color, offset, blur, spread)** | Yes | ❌ No | Yes | Paint / Shadow Pass |

---

## Part 3: First-Class Shared Shadow System (`std/graphics/shadow.lm`)

Limit introduces a unified, reusable `Shadow` frame across all style and graphics modules:

```limit
frame Shadow {
    pub var r: float;
    pub var g: float;
    pub var b: float;
    pub var a: float;
    pub var offset_x: float;
    pub var offset_y: float;
    pub var blur_radius: float;
    pub var spread_radius: float;
}
```

### Integration Points
1. **Graphics Core (`std/graphics/shadow.lm`)**: Provides `Shadow` frame, `shadow(...)` constructor, and `lerp_shadow(s1, s2, t)` generic interpolation.
2. **Graphics Canvas (`std/graphics/canvas.lm`)**: Implements `cvs.draw_shadow(rect, shadow)`.
3. **Renderer Primitive (`std.gg`)**: Implements `draw_shadow_primitive(x, y, w, h, r, g, b, a, off_x, off_y, blur, spread)`.
4. **Style Integration**: Added as a first-class property in `ui.Style`, `ui.Widget`, and `types.GUITheme`.

---

## Part 4: Hardened Unified Animation System (`std.animation`)

### Key Enhancements Implemented
1. **Interruptible Target Transitions**: Smoothly preserves current visual position and velocity when targets change mid-animation (`start_val = current_val`).
2. **Time-Step Aware Spring Physics**: Damped harmonic oscillator model (`stiffness`, `damping`, `mass`, `velocity`) stable across variable `dt` (30/60/120 FPS).
3. **Multi-Stage Keyframes (`Keyframes`)**: Interpolates multi-point keyframe sequences (`.add(progress, value)`).
4. **Animation Composition (`AnimationSequence`)**: Sequenced multi-stage animation chains.
5. **Timeline Controls**: Adds `.seek(progress)`, `.pause()`, `.resume()`, and `.reset()` control APIs.
6. **Centralized Accessibility Preferences (`AnimationPreferences`)**: Global preferences for `enabled`, `reduce_motion`, and `duration_scale`. When `reduce_motion = true`, animations instantly resolve to target values.
7. **Transition Lifecycle (`LIFECYCLE_ENTERING`, `LIFECYCLE_ACTIVE`, `LIFECYCLE_EXITING`, `LIFECYCLE_REMOVED`)**: Retained widgets process enter/exit transitions gracefully before node removal.
8. **IMGUI TTL State Cleanup**: `IMGUIAnimationStore` tracks frame counters (`last_used_frame`) and prunes stale transient animation state.

---

## Part 5: Comprehensive Test & Showcase Verification

1. **`tests/animation_test.lm`**:
   - `test_time_based_property_animation()` (PASSED)
   - `test_interruptible_target_changes()` (PASSED)
   - `test_spring_physics()` (PASSED)
   - `test_imgui_animation_store()` (PASSED)
   - `test_retained_ui_animation_modifiers()` (PASSED)
   - `test_shadow_interpolation()` (PASSED)
   - `test_keyframes_and_controls()` (PASSED)
   - `test_reduced_motion()` (PASSED)
   - `test_widget_lifecycle_transitions()` (PASSED)
2. **UI Integration Tests**:
   - `tests/ui_fluent_test.lm` (PASSED)
   - `tests/retained_ui_test.lm` (PASSED)
   - `tests/showcase_verify_test.lm` (PASSED)
3. **Showcase Applications**:
   - `gui_showcase.lm` (Verified)
   - `game_showcase.lm` (Verified)

---

## Conclusion

Limit's Unified Animation System provides production-quality animation capabilities comparable to modern frameworks (SwiftUI, Flutter, Qt, Compose, ImGui) while strictly preserving Limit's single-core architecture, zero-DOM game IMGUI performance, and fluent declarative UI style.
