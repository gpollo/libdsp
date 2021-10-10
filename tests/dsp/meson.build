subdir('filter')
subdir('window')

test('dsp/crop',
    executable('test-crop', ['crop.cpp'],
        include_directories: libdsp_include,
    )
)

test('dsp/delay-digital-signal',
    executable('test-delay-digital-signal', ['delay-digital-signal.cpp'],
        include_directories: libdsp_include,
    )
)

test('dsp/derivative',
    executable('test-derivative', ['derivative.cpp'],
        include_directories: libdsp_include,
    )
)

test('dsp/integral',
    executable('test-integral', ['integral.cpp'],
        include_directories: libdsp_include,
    )
)

test('dsp/partial-linear-map',
    executable('test-partial-linear-map', ['partial-linear-map.cpp'],
        include_directories: libdsp_include,
    )
)

test('dsp/rate-limiter',
    executable('test-rate-limiter', ['rate-limiter.cpp'],
        include_directories: libdsp_include,
    )
)