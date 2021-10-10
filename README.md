# libdsp

A small C++17 template-based library that provides various useful
classes for digital signal processing.

## Usage

To use this library, simply add `include/` to your include directory paths.

You can also use this repository as a [Meson subproject](https://mesonbuild.com/Subprojects.html).

See `examples/` for various examples.


## API

The following table presents the available functor classes in this library.

| Category | Class                                   | Description                              |
|:---------|:----------------------------------------|:-----------------------------------------|
| Filter   | `dsp::filter::convolution`              | Convolution-based filter.                |
|          | `dsp::filter::recursive`                | Recursion-based filter.                  |
|          | `dsp::filter::chebyshev::low_pass`      | Chebyshev digital filter (experimental). |
|          | `dsp::filter::chebyshev::high_pass`     | Chebyshev digital filter (experimental). |
|          | `dsp::filter::windowed_sinc::low_pass`  | Windowed-sinc digital filter.            |
|          | `dsp::filter::windowed_sinc::high_pass` | Windowed-sinc digital filter.            |
|          | `dsp::filter::moving_average`           | Fast moving average digital filter.      |
|          | `dsp::filter::all_pass`                 | Placebo digital filter.                  |
| Misc.    | `dsp::filter::derivative`               | Derivate the input signal.               |
|          | `dsp::filter::integral`                 | Integrate the input signal.              |
|          | `dsp::filter::pid`                      | Simple PID controller.                   |
|          | `dsp::filter::maximizer`                | Track the highest value encountered.     |
|          | `dsp::filter::minimizer`                | Track the lowest value encountered.      |
|          | `dsp::filter::rate_limiter`             | Limit the rate of change of the signal.  |
|          | `dsp::filter::partial_linear_map`       | Partial linear mapping between 2 points. |
|          | `dsp::filter::delay_digital_signal`     | Delay rising/falling edge signal.        |