project('martin-plus-plus', 'c')

src_files = files(
  'src/board.c',
  'src/magic_bit_board.c',
  'src/magic_bit_board_constants.c',
  'src/main.c',
)

include_dirs = include_directories('include')

executable('martin-gen', 'gen/magic_bit_board_gen.c')
executable('martin-plus-plus', src_files, include_directories: include_dirs)
