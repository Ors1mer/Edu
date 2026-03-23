program FloatingCrt;
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

procedure move_coords(var key, x, y: integer; msg: string);
const
    UpArr = -80;
    DownArr = -72;
    RightArr = -77;
    LeftArr = -75;
begin
    case key of
        UpArr: begin
            if y < ScreenHeight then
                y := y + 1
        end;
        DownArr: begin
            if y > 0 then
                y := y - 1
        end;
        RightArr: begin
            if x+length(msg)-1 < ScreenWidth then
                x := x + 1
        end;
        LeftArr: begin
            if x > 0 then
                x := x - 1
        end;
    end;
end;

procedure print_message(x, y: integer; msg: string);
begin
    clrscr;
    GotoXY(x, y);
    write(Msg);
    GotoXY(1, ScreenHeight);
end;


const
    Msg = 'Don''t believe what''s on TV' ;
var
    Center_x, Center_y: integer;
    x, y: integer;
    key: integer;
begin
    Center_x := ScreenWidth div 2;
    Center_y := ScreenHeight div 2;
    clrscr;
    { Print greeting }
    x := Center_x - (length(Msg) div 2);
    y := Center_y;
    print_message(x, y, Msg);
    { Moving the greeting }
    repeat
        GetKey(key);
        move_coords(key, x, y, Msg);
        print_message(x, y, Msg);
    until (key > 0);
    clrscr;
end.
