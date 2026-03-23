unit binary_trees_cycle; 
interface
uses tree_type;

function SearchTree(var p: TreeNodePtr; val: longint): TreeNodePos;
function SumTree(var p: TreeNodePtr): longint;

implementation

function SearchTree(var p: TreeNodePtr; val: longint): TreeNodePos;
var
    pp: TreeNodePos;
begin
    pp := @p;
    while (pp^ <> nil) and (pp^^.data <> val) do begin
        if val > pp^^.data then
            pp := @(pp^^.right)
        else if val < pp^^.data then
            pp := @(pp^^.left)
    end;
    SearchTree := pp;
end;

function SumTree(var p: TreeNodePtr): longint;
begin
    if p = nil then
        SumTree := 0
    else
        SumTree := SumTree(p^.left) + p^.data + SumTree(p^.right)
end;

begin
    {writeln(#10'Non-recursive functions were loaded.');}
end.
