project('martin-plus-plus', 'c')

src_files = files(
  'src/attacks.c',
  'src/board.c',
)

include_dirs = include_directories('include')

lib = static_library('martinlib', src_files, include_directories: include_dirs)

executable(
  'martin-plus-plus',
  'src/main.c',
  include_directories: include_dirs,
  link_with: lib,
)

test_executable = executable(
  'martin-plus-plus-test',
  'tests/tests.c',
  include_directories: include_dirs,
  link_with: lib,
)

test('all', test_executable)
