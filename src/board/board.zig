const std = @import("std");

pub const Board = struct {
    pieces: [12]u64,

    const Self = @This();
    const BoardIterator = struct {
        index: u64,

        fn next(self: *BoardIterator) ?u64 {
            if (self.index >= 64) {
                return null;
            }

            self.index += 1;
            return @as(u64, 1) << self.index;
        }
    };
    const PIECE_CHARS: [6]u8 = .{ 'P', 'K', 'Q', 'N', 'B', 'R' };
    const EMPTY_PIECE = '.';

    pub fn init() Self {
        return Self{
            .pieces = .{0} ** 12,
        };
    }

    pub fn print(self: Self) void {
        for (0..64) |j| {
            const pos = @as(u64, 1) << @as(u6, @intCast(j));
            var found_piece = false;

            for (0..self.pieces.len) |i| {
                const board = self.pieces[i];

                if ((board & pos) != 0) {
                    found_piece = true;
                    var idx = i;
                    if (i >= 6) {
                        idx -= 6;
                    }
                    const ch = PIECE_CHARS[i];
                    std.debug.print(" {c} ", .{ch});
                    break;
                }
            }

            if (!found_piece) {
                std.debug.print(" {c} ", .{EMPTY_PIECE});
            }

            if (j % 8 == 0) {
                std.debug.print("\n", .{});
            }
        }
    }

    pub fn iter() BoardIterator {
        return .{ .index = 0 };
    }
};

test "print" {
    const board = Board.init();
    board.print();
}
