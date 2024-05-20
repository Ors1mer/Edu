unit tree_type;
interface

type
    TreeNodePtr = ^TreeNode;
    TreeNodePos = ^TreeNodePtr;
    TreeNode = record
        data: longint;
        left, right: TreeNodePtr;
    end;

implementation

begin end.
