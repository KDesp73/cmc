# cmc

`C`hess `M`ove `C`hecker

A cli tool to check whether a chess move is valid or not

## Dependencies

- make
- cmake

## Installation

```console
git clone --depth=1 https://github.com/KDesp73/cmc
cd cmc
./install.sh
```

## Usage

```console
cmc --fen [FEN] --move [Move]
```

### Example

```console
cmc --move e2e4
```

Since `--fen` is not specified the starting chess position is being used

## Help

Try `cmc --help` or `man cmc`

## License

[GNU](./LICENSE)

## Author

[KDesp73](https://gitub.com/KDesp73)

