#include "piece.h"
#include "board.h"
#include "core.h"
#include "moves.h"

const Piece PIECES[6] = {
	[W_PAWN] = { 1, 'P', pawn_move_callback, pawn_attack_callback },
	[W_KING] = { 0, 'K', king_move_callback, NULL },
	[W_QUEEN] = { 9, 'Q', queen_move_callback, NULL },
	[W_ROOK] = { 5, 'R', rook_move_callback, NULL },
	[W_BISHOP] = { 3, 'R', bishop_move_callback, NULL },
	[W_KNIGHT] = { 3, 'N', knight_move_callback, NULL },
};

BitBoard piece_move(Piece piece, Board *board, Square square) {
	return piece.move_callback(board, square);
}

BitBoard piece_attack(Piece piece, Board *board, Square square) {
	if (!piece.attack_callback) {
		return piece.move_callback(board, square);
	}

	return piece.attack_callback(board, square);
}

BitBoard pawn_move_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	PieceType piece_type = board_get_piece(board, square);
	bool is_black = piece_type_is_black(piece_type);
	BitBoard en_passant_pos;

	BitBoard enemy_pawns = board->pieces[W_PAWN + (!is_black * 6)];

	BitBoard moves = pawn_move(square, is_black, blockers, enemy_pawns, &en_passant_pos);

	moves &= ~blockers;
	moves &= ~en_passant_pos;
	return moves;
}

BitBoard king_move_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	return cardinal_slider_move(square, blockers, 1) | orthagonal_slider_move(square, blockers, 1);
}

BitBoard queen_move_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	return cardinal_slider_move(square, blockers, 7) | orthagonal_slider_move(square, blockers, 7);
}

BitBoard rook_move_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	return cardinal_slider_move(square, blockers, 7);
}

BitBoard bishop_move_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	return orthagonal_slider_move(square, blockers, 7);
}

BitBoard knight_move_callback(Board *board, Square square) {
	UNUSED(board);
	return knight_move(square);
}

BitBoard pawn_attack_callback(Board *board, Square square) {
	BitBoard blockers = board_get_blockers(board, square);
	PieceType piece_type = board_get_piece(board, square);
	bool is_black = piece_type_is_black(piece_type);
	BitBoard en_passant_pos;

	BitBoard enemy_pawns = board->pieces[W_PAWN + (!is_black * 6)];

	BitBoard moves = pawn_move(square, is_black, blockers, enemy_pawns, &en_passant_pos);

	moves &= blockers & ~board_get_friendlies(board, is_black);
	return moves;
}
