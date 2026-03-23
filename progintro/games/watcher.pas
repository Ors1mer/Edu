program WatcherCrt;
uses crt;

procedure GetKey(var code: integer);
var 
    c: char;
begin
    c := ReadKey;
    if c = #0 then begin { extended key }
        c := ReadKey;
        code := -ord(c)
    end
    else begin           { regular key }
        code := ord(c)
    end
end;

procedure move_coordX(var x: integer; var direction: boolean);
begin
    if direction and (x < ScreenWidth) then begin { If can move right }
        x := x + 1
    end
    else if x = ScreenWidth then begin { Start moving left }
        direction := false;
        x := x - 1
    end
    else if x = 0 then begin { Start moving right }
        direction := true;
        x := x + 1
    end
    else begin { Continue moving left }
        x := x - 1
    end
end;

procedure print_message(x, y: integer; msg: string);
begin
    clrscr;
    GotoXY(x, y);
    write(Msg);
    GotoXY(1, ScreenHeight);
end;


const
    Msg = '*';
    DelayDuration = 100;
var
    Center_x, Center_y: integer;
    x, y: integer;
    key: integer;
    right_d: boolean = true; { move right }
begin
    Center_x := ScreenWidth div 2;
    Center_y := ScreenHeight div 2;
    clrscr;
    { Print * }
    x := Center_x;
    y := Center_y;
    print_message(x, y, Msg);
    { Moving the * }
    repeat
        move_coordX(x, right_d);
        print_message(x, y, Msg);
        delay(DelayDuration);

        if KeyPressed then
            GetKey(key);
    until (key > 0);
    clrscr;
end.
