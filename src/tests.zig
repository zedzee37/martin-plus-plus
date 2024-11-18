const std = @import("std");
pub const main = @import("main.zig");

test {
    _ = std.testing.refAllDeclsRecursive(@This());
}
