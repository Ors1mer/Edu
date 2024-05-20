program ManyDiamonds;

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
    print_symbols(n+2-r, ' ');
end;

procedure print_lines(amount, n, r: integer);
var
    i: integer;
begin
    for i := 1 to amount do
        print_line(n, r);
    writeln;
end;

var
    height, amount: integer;
    n, r: integer;
begin
    repeat
        write('Enter the height (positive odd) and the amount of diamonds: ');
        read(height);
        readln(amount);
    until (height > 0) and (height mod 2 = 1) and (amount > 0);
    writeln;
    n := height div 2;

    for r := 1 to n + 1 do begin
        print_lines(amount, n, r);
    end;
    
    for r := n downto 1 do begin
        print_lines(amount, n, r);
    end;
    writeln;
end.
