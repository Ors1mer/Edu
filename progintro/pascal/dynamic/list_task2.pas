program list_task2;

type
    itemptr = ^item;
    item = record
        data: integer;
        next: itemptr;
    end;

procedure show_list(var first, last: itemptr);
begin
    repeat
        writeln(first^.data);
        first := first^.next;
    until (first^.next = last^.next);
end;
var
    elem: integer;
    first, last, t: itemptr;
begin
    new(first);
    last := first;
    while not eof do begin
        read(elem);
        last^.data := elem;
        t := last;
        new(last);
        t^.next := last;
    end;
    last^.next := first;
    writeln(#10'Printng elements in the same order: ');
    show_list(first, last);
    writeln('And again: ');
    first := last^.next;
    show_list(first, last);
end.
