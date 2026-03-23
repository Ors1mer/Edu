program ColorsCrt;
uses crt;

procedure print_message(x, y: integer; msg: string);
begin
    GotoXY(x, y);
    write(Msg);
end;


const
    Msg = 'No Chances!';
var
    x, y: integer;
begin
    clrscr;
    x := 1;
    y := 1;
    TextColor(Black);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Blue or Blink);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Green);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Cyan);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Red);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Magenta);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Brown);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightGray);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(DarkGray);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightBlue);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightGreen);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightCyan);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightRed);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(LightMagenta);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(Yellow);
    print_message(x, y, msg);
    y := y + 1;
    TextColor(White);
    print_message(x, y, msg);
end.
