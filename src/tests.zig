const std = @import("std");
pub const main = @import("main.zig");
pub const board = @import("board");

test {
    _ = std.testing.refAllDeclsRecursive(@This());
}
