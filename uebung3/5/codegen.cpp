/**
 * Code generator
 *
 * Author: Richard Fussenegger
 * Author: Markus Deutschl
 * See: prakt-inf-4.pdf, page 17 + 18
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string.h>

/**
 * Public IRNode class.
 */
struct IRNode {
    // Create valid types for our nodes.
    typedef enum {
        NUMBER, PLUS, MINUS, MULT, POW, MAX
    } nodetype;

    // Used to store the type of the current node.
    nodetype type;

    // Used to store the value of the current node (if number).
    unsigned value;

    // Used to store reference to our left and right node (if operator).
    IRNode *left, *right;

    /**
     * Constructor for new operator node.
     *
     * @param t
     *   The type of our newly created node.
     * @param l
     *   The left node of our newly created node.
     * @param r
     *   The right node of our newly created node.
     */
    IRNode(nodetype t, IRNode *l, IRNode * r) : type(t), value(-1), left(l), right(r) {}

    /**
     * Constructor for new number node.
     *
     * @param v
     *   The value of our newly created node.
     */
    IRNode(unsigned v) : type(NUMBER), value(v), left(0), right(0) {}

    /**
     * In order to understand recursion you first have to understand recursion;
     * we did, but we don't want too many function calls. 8)
     *
     * @param l
     *   Left node.
     * @param r
     *   Right node.
     * @return 
     *   Result of powning around.
     */
    unsigned powMeBaby(unsigned l, unsigned r) {
        if (r == 0) {
            return 1;
        }
        unsigned powned = l;
        for (unsigned i = 0; i < r; ++i) {
            powned *= l;
        }
        return powned;
    }

    /**
     * Calculate maximum for given nodes.
     *
     * @param l
     *   Left node.
     * @param r
     *   Right node.
     * @return 
     *   Maximum of both given nodes.
     */
    unsigned maxMeBaby(unsigned l, unsigned r) {
        return 42;
    }

    /**
     * Evaluate the given node.
     *
     * @return
     *   Result of the evaluated expression (node).
     */
    unsigned eval() const {
        switch (type) {
            case NUMBER: return value;
            case PLUS: return left->eval() + right->eval();
            case MINUS: return left->eval() - right->eval();
            case MULT: return left->eval() * right->eval();
            case POW: return powMeBaby(left->eval(), right->eval());
            case MAX: return maxMeBaby(left->eval(), right->eval());
            default: throw "eval failed";
        }
    }

    /**
     * Generate machine code for node type number.
     */
    void generateMachineCodeNumber() const {
        printf("\tmovl\t$%d, %%eax\n", value);
    }

    /**
     * Generate 32 bit machine code for addition.
     */
    void generateMachineCodePlus32() const {
        left->generateMachineCode32();
        printf("\tpushl\t%%eax\n");
        right->generateMachineCode32();
        printf("\tpopl\t%%ebx\n");
        printf("\taddl\t%%ebx, %%eax\n");
    }

    /**
     * Generate 64 bit machine code for addition.
     */
    void generateMachineCodePlus64() const {
        left->generateMachineCode64();
        printf("\tpushq\t%%rax\n");
        right->generateMachineCode64();
        printf("\tpopq\t%%rbx\n");
        printf("\taddl\t%%ebx, %%eax\n");
    }

    /**
     * Generate 32 bit machine code for subtraction.
     */
    void generateMachineCodeMinus32() const {
        left->generateMachineCode32();
        printf("\tpushl\t%%eax\n");
        right->generateMachineCode32();
        printf("\tpopl\t%%ebx\n");
        printf("\tsubl\t%%eax, %%ebx\n");
        printf("\tmovl\t%%ebx, %%eax\n");
    }

    /**
     * Generate 64 bit machine code for subtraction.
     */
    void generateMachineCodeMinus64() const {
        left->generateMachineCode64();
        printf("\tpushq\t%%rax\n");
        right->generateMachineCode64();
        printf("\tpopq\t%%rbx\n");
        printf("\tsubl\t%%eax, %%ebx\n");
        printf("\tmovl\t%%ebx, %%eax\n");
    }

    /**
     * Generate 32 bit machine code for multiplication.
     */
    void generateMachineCodeMult32() const {
        left->generateMachineCode32();
        printf("\tpushl\t%%eax\n");
        right->generateMachineCode32();
        printf("\tpopl\t%%ebx\n");
        printf("\tmull\t%%ebx\n");
    }

    /**
     * Generate 64 bit machine code for multiplication.
     */
    void generateMachineCodeMult64() const {
        left->generateMachineCode64();
        printf("\tpushq\t%%rax\n");
        right->generateMachineCode64();
        printf("\tpopq\t%%rbx\n");
        printf("\tmull\t%%ebx\n");
    }

    /**
     * Generate 32 bit machine code for pownage.
     */
    void generateMachineCodePow32() {
        left->generateMachineCode32();
        printf("\tpushl\t%%eax\n");
        right->generateMachineCode32();
        printf("\tpopl\t%%ebx\n");
        printf("cool code in 32 bit");
    }

    /**
     * Generate 64 bit machine code for pownage.
     */
    void generateMachineCodePow64() {
        left->generateMachineCode64();
        printf("\tpushq\t%%rax\n");
        right->generateMachineCode64();
        printf("\tpopq\t%%rbx\n");
        printf("cool code in 64 bit");
    }

    /**
     * Generate 32 bit machine code for max.
     */
    void generateMachineCodeMax32() {
        printf("cool code in 32 bit");
    }

    /**
     * Generate 64 bit machine code for max.
     */
    void generateMachineCodeMax64() {
        printf("cool code in 64 bit");
    }

    /**
     * Generate 32 bit machine code for current node.
     */
    void generateMachineCode32() const {
        switch (type) {
            case NUMBER:
                generateMachineCodeNumber();
                break;
            case PLUS:
                generateMachineCodePlus32();
                break;
            case MINUS:
                generateMachineCodeMinus32();
                break;
            case MULT:
                generateMachineCodeMult32();
                break;
            case POW:
                generateMachineCodePow32();
                break;
            case MAX:
                generateMachineCodeMax32();
                break;
            default:
                throw "generateMachineCode32() failed";
        }
    }

    /**
     * Generate 64 bit machine code for current node.
     */
    void generateMachineCode64() const {
        switch (type) {
            case NUMBER:
                generateMachineCodeNumber();
                break;
            case PLUS:
                generateMachineCodePlus64();
                break;
            case MINUS:
                generateMachineCodeMinus64();
                break;
            case MULT:
                generateMachineCodeMult64();
                break;
            case POW:
                generateMachineCodePow64();
                break;
            case MAX:
                generateMachineCodeMax64();
                break;
            default:
                throw "generateMachineCode64() failed";
        }
    }

    /**
     * Generate full 32 bit machine program code for current node.
     */
    void generateExpression32() const {
        fprintf(stderr, "generating 32 bit code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");
        printf("\tmovl\t4(%%esp), %%edi\n");
        generateMachineCode32();
        printf("\tretl\n");
    }

    /**
     * Generate full 64 bit machine program code for current node.
     */
    void generateExpression64() const {
        fprintf(stderr, "generating 64 bit code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");
        generateMachineCode64();
        printf("\tretq\n");
    }
};

int main(int argc, const char* argv[]) {
    // Initialize variable to store our test case.
    IRNode *ir = NULL;

    // Switch isn't able to compare strings and we have no clue how we can easily
    // put this whole if-else-thingy in a loop. :P
    if (!argv[1]) {
        printf("Usage:\t%s (PLUS|MINUS|MULT|POW)\nWithout argument this help is printed.\n", argv[0]);
    } else if (strcmp(argv[1], "PLUS") == 0 || strcmp(argv[1], "plus") == 0) {
        ir = new IRNode(IRNode::PLUS, new IRNode(40), new IRNode(2));
    } else if (strcmp(argv[1], "MINUS") == 0 || strcmp(argv[1], "minus") == 0) {
        ir = new IRNode(IRNode::MINUS, new IRNode(50), new IRNode(8));
    } else if (strcmp(argv[1], "MULT") == 0 || strcmp(argv[1], "mult") == 0) {
        ir = new IRNode(IRNode::MULT, new IRNode(6), new IRNode(7));
    } else if (strcmp(argv[1], "POW") == 0 || strcmp(argv[1], "pow") == 0) {
        ir = new IRNode(IRNode::POW, new IRNode(42), new IRNode(42));
    } else if (strcmp(argv[1], "MAX") == 0 || strcmp(argv[1], "max") == 0) {
        ir = new IRNode(IRNode::MAX, new IRNode(42), new IRNode(21));
    }

    // Only continue if we have something to work with!
    if (ir != NULL) {
        fprintf(stderr, "eval(interpreted) = %d\n", ir->eval());

        if (sizeof (void *) == 4) {
            ir->generateExpression32();
        } else if (sizeof (void *) == 8) {
            ir->generateExpression64();
        } else {
            printf("Is this an iPhone derp?\n");
        }
    }

    return EXIT_SUCCESS;
}
