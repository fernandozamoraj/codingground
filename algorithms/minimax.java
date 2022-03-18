class Node{
  public Node left;
  public Node right;
  public int value;
  public String id;
  public Node(int value, String id){
    left = right = null;
    this.value = value;
    this.id = id;
  }
  public boolean isLeaf(){
    return left == null && right == null;
  }
}

class Main {
  private static final int INFINITY = 9999; //9999 good enough for this
  public static void main(String[] args) {
    Node root = createTree();
    int max = minimax(root, 0, true, -INFINITY, INFINITY);
    System.out.println("Max is " + max);
  }

  private static Node createTree(){
    Node root = new Node(0, "root");

    Node n1 = new Node(5, "n1");
    Node n2 = new Node(17, "n2");
    Node n3 = new Node(17, "n3");
    Node n4 = new Node(7, "n4");
    Node n5 = new Node(-3, "n5");
    Node n6 = new Node(6, "n5");
    Node n7 = new Node(-1, "n7");
    Node n8 = new Node(6, "n8");

    Node maxGC1 = new Node(0, "maxGC1");
    Node maxGC2 = new Node(0, "maxGC2");
    Node maxGC3 = new Node(0, "maxGC3");
    Node maxGC4 = new Node(0, "maxGC4");

    maxGC1.left = n1;
    maxGC1.right = n2;

    maxGC2.left = n3;
    maxGC2.right = n4;

    maxGC3.left = n5;
    maxGC3.right = n6;

    maxGC4.left = n7;
    maxGC4.right = n8;

    Node minC1 = new Node(0, "minC1");
    Node minC2 = new Node(0, "minC2");

    minC1.left = maxGC1;
    minC1.right = maxGC2;

    minC2.left = maxGC3;
    minC2.right = maxGC4;

    root.left = minC1;
    root.right = minC2;
    return root;
  }
  private static int max(int a, int b){
    if(a >= b){
      return a;
    }
    return b;
  }

  private static int min(int a, int b){
    if(a < b){
      return a;
    }
    return b;
  }
  
  private static int minimax(
    Node node, int depth, 
    boolean isMaximizingPlayer, 
    int alpha, int beta){

    if(node.isLeaf())
        return node.value;
    
    if(isMaximizingPlayer){
        int bestVal = -INFINITY; 
        Node[] children = new Node[]{node.left, node.right};
      
        for(Node childNode: children){
          if(childNode == null) continue;
          
          int value = minimax(childNode, depth+1, false, alpha, beta);
          bestVal = max( bestVal, value); 
          alpha = max(alpha, bestVal);
          if( beta <= alpha){
              System.out.println("Pruned at id: v/a/b " + node.id + ": " + value + "/" + alpha + "/" + beta);
              break;
          }

        }   
      
        return bestVal;
    }
    else{
        int bestVal = INFINITY;
        Node[] children = new Node[]{node.left, node.right};
        for(Node childNode: children){
            int value = minimax(childNode, depth+1, true, alpha, beta);
            bestVal = min( bestVal, value);
            beta = min(beta, bestVal);
            if(beta <= alpha){
              System.out.println("Pruned at id: v/a/b " + node.id + ": " + value + "/" + alpha + "/" + beta);
              break;
            }
        }
      
        return bestVal;
    }
  }
}
