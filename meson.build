project('master', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: 'latest',
)

cpp_compiler = meson.get_compiler('cpp')
cpp_args = []

###################################
# -Dwith-libquadmath build option #
###################################

libquadmath_dep = cpp_compiler.find_library('quadmath', required: get_option('with-libquadmath'))
libquadmath_is_enabled = libquadmath_dep.found()
if libquadmath_is_enabled
    cpp_args += '-DLIBDSP_LIBQUADMATH_SUPPORT'
endif

##########
# libdsp #
##########

libdsp_include = include_directories('include')

############
# examples #
############

subdir('examples')

#########
# tests #
#########

subdir('tests')

#################
# format target #
#################

if build_machine.system() == 'linux'
    format_include = '`find include -type f -iname \'*.hpp\'`'
    format_examples = '`find examples -type f -iname \'*.cpp\'`'
    format_tests = '`find tests -type f -iname \'*.cpp\'`'
    format_files = '@0@ @1@ @2@'.format(format_include, format_examples, format_tests)

    run_target('format',
        command: [
            'sh', '-c',
            'cd @0@ && clang-format --verbose -i @1@'.format(
                meson.source_root(),
                format_files,
            )
        ],
    )
endif

###############
# tidy target #
###############

if build_machine.system() == 'linux'
    tidy_include = '`find include -type f -iname \'*.hpp\'`'
    tidy_examples = '`find examples -type f -iname \'*.cpp\'`'
    tidy_tests = '`find tests -type f -iname \'*.cpp\'`'
    tidy_files = '@0@ @1@ @2@'.format(tidy_include, tidy_examples, tidy_tests)

    run_target('tidy',
        command: [
            'sh', '-c',
            'cd @0@ && clang-tidy -p=@1@ @2@'.format(
                meson.source_root(),
                meson.current_build_dir(),
                tidy_files,
            )
        ],
    )
endif
