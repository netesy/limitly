const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Define the main executable
    const exe = b.addExecutable(.{
        .name = "limitly",
        .target = target,
        .optimize = optimize,
    });

    // Set language to C++
    exe.linkLibCpp();
    
    // Add source files
    const cpp_flags = [_][]const u8{"-std=c++17", "-fno-rtti"};
    
    // Main file
    exe.addCSourceFile(.{
        .file = .{ .path = "main.cpp" },
        .flags = &cpp_flags,
    });
    
    // Frontend files
    exe.addCSourceFile(.{
        .file = .{ .path = "frontend/scanner.cpp" },
        .flags = &cpp_flags,
    });
    
    exe.addCSourceFile(.{
        .file = .{ .path = "frontend/parser.cpp" },
        .flags = &cpp_flags,
    });
    
    // Backend files
    exe.addCSourceFile(.{
        .file = .{ .path = "backend/backend.cpp" },
        .flags = &cpp_flags,
    });
    
    exe.addCSourceFile(.{
        .file = .{ .path = "backend/vm.cpp" },
        .flags = &cpp_flags,
    });
    
    // Shared files
    exe.addCSourceFile(.{
        .file = .{ .path = "debugger.cpp" },
        .flags = &cpp_flags,
    });
    
    // Add include directories
    exe.addIncludePath(.{ .path = "." });
    
    // Install the executable
    b.installArtifact(exe);
    
    // Define the test_parser executable
    const test_parser = b.addExecutable(.{
        .name = "test_parser",
        .target = target,
        .optimize = optimize,
    });
    
    // Set language to C++
    test_parser.linkLibCpp();
    
    // Add source files
    test_parser.addCSourceFile(.{
        .file = .{ .path = "test_parser.cpp" },
        .flags = &cpp_flags,
    });
    
    test_parser.addCSourceFile(.{
        .file = .{ .path = "frontend/scanner.cpp" },
        .flags = &cpp_flags,
    });
    
    test_parser.addCSourceFile(.{
        .file = .{ .path = "frontend/parser.cpp" },
        .flags = &cpp_flags,
    });
    
    test_parser.addCSourceFile(.{
        .file = .{ .path = "backend/backend.cpp" },
        .flags = &cpp_flags,
    });
    
    test_parser.addCSourceFile(.{
        .file = .{ .path = "debugger.cpp" },
        .flags = &cpp_flags,
    });
    
    // Add include directories
    test_parser.addIncludePath(.{ .path = "." });
    
    // Install the test_parser executable
    b.installArtifact(test_parser);
    
    // Create run step for the main executable
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
    
    // Create run step for the test_parser executable
    const run_test_parser = b.addRunArtifact(test_parser);
    run_test_parser.step.dependOn(b.getInstallStep());
    run_test_parser.addArg("sample.lm");
    const test_parser_step = b.step("test-parser", "Run the test parser on sample.lm");
    test_parser_step.dependOn(&run_test_parser.step);
}