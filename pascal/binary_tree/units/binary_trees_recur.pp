unit binary_trees_recur;
interface
uses tree_type;

function SearchTree(var p: TreeNodePtr; val: longint): TreeNodePos;
function SumTree(var p: TreeNodePtr): longint;

implementation

function SearchTree(var p: TreeNodePtr; val: longint): TreeNodePos;
begin
    if (p = nil) or (p^.data = val) then
        SearchTree := @p
    else if val < p^.data then
        SearchTree := SearchTree(p^.left, val)
    else
        SearchTree := SearchTree(p^.right, val)
end;

function SumTree(var p: TreeNodePtr): longint;
begin
    if p = nil then
        SumTree := 0
    else
        SumTree := SumTree(p^.left) + p^.data + SumTree(p^.right)
end;

begin
    {writeln(#10'Recursive functions were loaded.');}
end.
