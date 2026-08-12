# Redundant Files, Classes, and Folders to Remove

The following files, directories, and assets are redundant, add no value, lead to more confusion, and can be safely removed from this project.

## 1. Duplicate & Leftover Test Directories

- **`tests/tl_stdlib/`**
  - *Description*: Contains an older/copied set of standard library tests. The active, standardized tests reside in `tests/stdlib/`.
- **`tests/tl_stdlib_orig/`**
  - *Description*: Contains original/unmodified versions of standard library tests. This is fully duplicate and superseded by `tests/stdlib/`.
- **`tests/stdlib/2`**
  - *Description*: A leftover temporary file containing a scratchpad test for `collections.Vector`. This was never properly named or integrated, and its behavior is already fully covered by `tests/stdlib/collections/vector_test.lm`.

## 2. Duplicate & Empty Standard Library Source Files

- **`std/ffi copy.lm`**
  - *Description*: An accidental file copy of `std/ffi.lm`. Leads to module resolution confusion and should be deleted.
- **`std/empty.lm`**
  - *Description*: A completely empty file in the standard library root directory with no declarations or value.

## 3. Redundant negative-testing Documentation Indices

- **`NEGATIVE_TESTING_FRAMEWORK_INDEX.md`**
  - *Description*: Redundant markdown index for negative testing. This is completely duplicates standard documentation and the negative testing README.
- **`NEGATIVE_TESTING_GETTING_STARTED.md`**
  - *Description*: Redundant guide.
- **`NEGATIVE_TESTING_SUMMARY.md`**
  - *Description*: Duplicate test summary report file.
- **`README_NEGATIVE_TESTING.md`**
  - *Description*: Duplicate/unneeded README on negative tests. The primary instructions are already fully covered in the main `README.md` and `tests/negative/README.md`.

## 4. Unneeded Temporary Log & Result Files

- **`results.md`**
  - *Description*: Leftover benchmark and test run result artifacts from past manual executions.
- **`test_failures_summary.md`**
  - *Description*: Temporary test failure log file that gets stale instantly.
- **`activities.md`**
  - *Description*: Miscellaneous artifact outlining user/agent activity.
- **`actions.md`**
  - *Description*: Miscellaneous task-tracking log file.
- **`REGRESSION_FIXES.md`**
  - *Description*: Stale documentation summarizing old fix logs.
- **`IMPLEMENTATION_COMPLETE.md`**
  - *Description*: Old implementation log document that adds no value to the current active codebase.
