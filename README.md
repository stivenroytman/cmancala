# cmancala

## Purpose
 
Purely for educational purposes. Also, pointers are fun!

## Installation & Usage

### Linux 

```bash
git clone https://github.com/stivenroytman/cmancala
cd cmancala
make
./mancala
```

### Windows

```powershell
$winbinman = "https://github.com/stivenroytman/cmancala/releases/download/v0.6/mancala_win-x86_64.exe"
Invoke-WebRequest $winbinman -OutFile mancala.exe
.\mancala.exe
```

## TODO

✔️ Text based display.

✔️ Move input from STDIN.

✔️ Validity of moves is checked.

✔️ The circular movement of pebbles works as expected.

✔️ Bonus move mechanic works.

Capture mechanic works.

Inputting chars instead of integers into move selection doesn't make it blow up.

Text based display doesn't get messed up when we reach double digits.
