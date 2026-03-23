program list_task1;

type
    itemptr = ^item;
    item = record
        data: integer;
        next: itemptr;
    end;
var
    elem: integer;
    first_p, t: itemptr;
begin
    t := nil;
    while not eof do begin
        new(first_p);
        first_p^.next := t;
        read(elem);
        first_p^.data := elem;
        t := first_p;
    end;
    writeln(#10'Printing entered data in reverse order: ');
    repeat
        writeln(first_p^.data);
        first_p := first_p^.next;
    until (first_p = nil);
end.
