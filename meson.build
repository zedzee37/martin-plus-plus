project('martin-plus-plus', 'c')

src_files = files(
  'src/attacks.c',
  'src/board.c',
  'src/main.c',
)

include_dirs = include_directories('include')

executable('martin-plus-plus', src_files, include_directories: include_dirs)
executable('martin-gen', 'gen/magic_bit_board_gen.c')
