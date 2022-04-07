program FilledDiamond;

procedure print_symbols(count: integer; sym: char);
var
    i: integer;
begin
    for i := 1 to count do
        write(sym)
end;

procedure print_line(n, r: integer);
begin
    print_symbols(n+1-r, ' ');
    write('*');
    if r > 1 then
       print_symbols(2*r - 2, '*'); 
    writeln;
end;

function ask_input(): integer;
var
    num: integer;
begin
    repeat
        write('Enter the height (positive odd): ');
        readln(num);
    until (num > 0) and (num mod 2 = 1);
    writeln;
    ask_input := num;
end;

var
    height: integer;
    n, r: integer;
begin
    height := ask_input();

    n := height div 2;

    for r := 1 to n + 1 do
        print_line(n, r);
    
    for r := n downto 1 do
        print_line(n, r);
    writeln;
end.
