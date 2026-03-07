const std = @import("std");

pub fn build(b: *std.Build) void {
	const target = b.standardTargetOptions(.{});
	const optimize = b.standardOptimizeOption(.{});

	const enable_ao = b.option(bool, "enable-ao", "Build audio support with libao") orelse false;

	const target_dir = target.result.zigTriple(b.allocator) catch @panic("OOM");
	const output_dir = b.fmt("{s}/{s}", .{ @tagName(optimize), target_dir });

	const libmorse = b.addLibrary(.{
		.name = "morse",
		.linkage = .static,
		.root_module = b.createModule(.{
			.target = target,
			.optimize = optimize,
			.strip = optimize != .Debug
		}),
	});
	libmorse.addCSourceFile(.{ .file = b.path("src/libmorse.c") });
	libmorse.addIncludePath(b.path("."));
	libmorse.linkLibC();
	libmorse.linkSystemLibrary("m");
	installArtifactInTargetDir(b, libmorse, output_dir, .lib);

	addTool(b, "morse-compress", "src/morse-compress.c", libmorse, target, optimize, output_dir);
	addTool(b, "morse-decode", "src/morse-decode.c", libmorse, target, optimize, output_dir);
	addTool(b, "morse-encode", "src/morse-encode.c", libmorse, target, optimize, output_dir);
	addTool(b, "morse-uncompress", "src/morse-uncompress.c", libmorse, target, optimize, output_dir);

	if (enable_ao) {
		const libmorsebeep = b.addLibrary(.{
			.name = "morsebeep",
			.linkage = .static,
			.root_module = b.createModule(.{
				.target = target,
				.optimize = optimize,
				.strip = optimize != .Debug
			}),
		});
		libmorsebeep.addCSourceFile(.{ .file = b.path("src/libmorsebeep.c") });
		libmorsebeep.addIncludePath(b.path("."));
		libmorsebeep.linkLibC();
		libmorsebeep.linkSystemLibrary("ao");
		libmorsebeep.linkSystemLibrary("m");
		installArtifactInTargetDir(b, libmorsebeep, output_dir, .lib);

		const audio = b.addExecutable(.{
			.name = "morse-audio",
			.root_module = b.createModule(.{
				.target = target,
				.optimize = optimize,
				.strip = optimize != .Debug
			}),
		});
		audio.addCSourceFile(.{ .file = b.path("src/morse-audio.c") });
		audio.addIncludePath(b.path("."));
		audio.linkLibC();
		audio.linkLibrary(libmorsebeep);
		audio.linkSystemLibrary("ao");
		audio.linkSystemLibrary("m");
		installArtifactInTargetDir(b, audio, output_dir, .bin);
	}
}

fn addTool(
	b: *std.Build,
	name: []const u8,
	source: []const u8,
	libmorse: *std.Build.Step.Compile,
	target: std.Build.ResolvedTarget,
	optimize: std.builtin.OptimizeMode,
	output_dir: []const u8,
) void {
	const exe = b.addExecutable(.{
		.name = name,
		.root_module = b.createModule(.{
			.target = target,
			.optimize = optimize,
			.strip = optimize != .Debug
		}),
	});
	exe.addCSourceFile(.{ .file = b.path(source) });
	exe.addIncludePath(b.path("."));
	exe.linkLibC();
	exe.linkLibrary(libmorse);
	exe.linkSystemLibrary("m");
	installArtifactInTargetDir(b, exe, output_dir, .bin);
}

fn installArtifactInTargetDir(
	b: *std.Build,
	artifact: *std.Build.Step.Compile,
	output_dir: []const u8,
	kind: enum { bin, lib },
) void {
	const subdir = switch (kind) {
		.bin => b.fmt("{s}/bin", .{output_dir}),
		.lib => b.fmt("{s}/lib", .{output_dir}),
	};

	const install = b.addInstallArtifact(artifact, .{
		.dest_dir = .{
			.override = .{
				.custom = subdir,
			},
		},
	});
	b.getInstallStep().dependOn(&install.step);
}
