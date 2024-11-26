project('martin-plus-plus', 'c')

src_files = files(
  'src/board.c',
  'src/square.c',
)

include_dirs = include_directories('include')

lib = static_library('martinlib', src_files, include_directories: include_dirs)

executable(
  'martin-plus-plus',
  'src/main.c',
  include_directories: include_dirs,
  link_with: lib,
)

test_files = [
]

foreach test : test_files
  test_name = test + '_test'
  test_exe = executable(
    test_name,
    'test/' + test + '.c',
    include_directories: include_dirs,
    link_with: lib,
  )
  test(test_name, test_exe)
endforeach
