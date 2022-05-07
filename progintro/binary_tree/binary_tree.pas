program binary_trees;
uses SysUtils, tree_type, binary_trees_cycle;

function IsInTree(p: TreeNodePtr; val: longint): boolean;
begin
    IsInTree := SearchTree(p, val)^ <> nil
end;

procedure AddToTree(var p: TreeNodePtr; var ok: boolean; val: longint);
var
    pos: TreeNodePos;
begin
    pos := SearchTree(p, val);
    if pos^ = nil then begin
        new(pos^);
        pos^^.data := val;
        pos^^.left := nil;
        pos^^.right := nil;
        ok := true
    end else begin
        ok := false
    end;
end;

var
    i: integer;
    el: longint;
    ok: boolean;
    p: TreeNodePtr = nil;
begin
    for i := 1 to ParamCount do begin
        el := StrToInt(ParamStr(i));
        AddToTree(p, ok, el)
    end;

    writeln(SumTree(p));
end.
