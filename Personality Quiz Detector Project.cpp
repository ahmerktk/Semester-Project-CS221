#include <iostream>
#include <string>
#include <stack>
using namespace std;

// ================= QUESTION DOUBLY LINKED LIST =================
struct Question
{
    string text;
    string options[4];
    char traits[4];
    Question *next;
    Question *prev;
};

Question *createQuestion(string t,
                         string o1, char c1,
                         string o2, char c2,
                         string o3, char c3,
                         string o4, char c4)
{
    Question *q = new Question();
    q->text = t;
    q->options[0] = o1;
    q->traits[0] = c1;
    q->options[1] = o2;
    q->traits[1] = c2;
    q->options[2] = o3;
    q->traits[2] = c3;
    q->options[3] = o4;
    q->traits[3] = c4;
    q->next = q->prev = NULL;
    return q;
}

// ================= TRAIT BST FOR CURRENT USER =================
struct TraitNode
{
    char trait;
    int score;
    TraitNode *left;
    TraitNode *right;
};

TraitNode *createTrait(char t)
{
    TraitNode *node = new TraitNode();
    node->trait = t;
    node->score = 1;
    node->left = node->right = NULL;
    return node;
}

TraitNode *insertTrait(TraitNode *root, char t)
{
    if (!root)
        return createTrait(t);
    if (t == root->trait)
        root->score++;
    else if (t < root->trait)
        root->left = insertTrait(root->left, t);
    else
        root->right = insertTrait(root->right, t);
    return root;
}

void decrementTrait(TraitNode *root, char t)
{
    if (!root)
        return;
    if (t == root->trait && root->score > 0)
        root->score--;
    else if (t < root->trait)
        decrementTrait(root->left, t);
    else
        decrementTrait(root->right, t);
}

int getScore(TraitNode *root, char t)
{
    if (!root)
        return 0;
    if (root->trait == t)
        return root->score;
    if (t < root->trait)
        return getScore(root->left, t);
    return getScore(root->right, t);
}

// ================= UI =================
void header()
{
    cout << "\n============================================\n";
    cout << "        MBTI PERSONALITY QUIZ\n";
    cout << "============================================\n";
    cout << "Choose A–D | X = Go Back\n";
    cout << "--------------------------------------------\n";
}

void describe(string type)
{
    cout << "\n============================================\n";
    cout << "        PERSONALITY INSIGHT\n";
    cout << "============================================\n";
    if (type == "INFP")
        cout << "Empathetic, idealistic, and creative.\n";
    else if (type == "INTJ")
        cout << "Strategic, analytical, and independent.\n";
    else if (type == "ENTJ")
        cout << "Confident, decisive leader.\n";
    else if (type == "ENFP")
        cout << "Energetic, imaginative, and people-driven.\n";
    else if (type == "ISTJ")
        cout << "Practical, responsible, and reliable.\n";
    else
        cout << "Balanced and adaptable personality.\n";
}

// ================= AVL TREE FOR LEADERBOARD =================
struct UserNode
{
    string name;
    int score;
    int height;
    UserNode *left;
    UserNode *right;
};

int getHeight(UserNode *node)
{
    return node ? node->height : 0;
}

int getBalance(UserNode *node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

UserNode *createUser(string name, int score)
{
    UserNode *node = new UserNode();
    node->name = name;
    node->score = score;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
UserNode *rightRotate(UserNode *y)
{
    UserNode *x = y->left;
    UserNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Left rotate
UserNode *leftRotate(UserNode *x)
{
    UserNode *y = x->right;
    UserNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Insert user into AVL tree (sorted by score descending)
UserNode *insertUser(UserNode *root, string name, int score)
{
    if (!root)
        return createUser(name, score);

    if (score > root->score)
        root->left = insertUser(root->left, name, score);
    else
        root->right = insertUser(root->right, name, score);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && score > root->left->score)
        return rightRotate(root);
    if (balance < -1 && score <= root->right->score)
        return leftRotate(root);
    if (balance > 1 && score <= root->left->score)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && score > root->right->score)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Display leaderboard descending
void displayLeaderboard(UserNode *root)
{
    if (!root)
        return;
    displayLeaderboard(root->left);
    cout << root->name << " : " << root->score << endl;
    displayLeaderboard(root->right);
}

// ================= QUIZ FUNCTION =================
int takeQuiz()
{
    // Create questions
    Question *q1 = createQuestion(
        "In a new environment, you prefer to:",
        "Stay reserved and observe", 'I',
        "Engage and talk to others", 'E',
        "Plan everything early", 'J',
        "Keep things flexible", 'P');
    Question *q2 = createQuestion(
        "You trust information that is:",
        "Based on facts and reality", 'S',
        "Based on patterns and ideas", 'N',
        "Logically sound", 'T',
        "Emotionally meaningful", 'F');
    Question *q3 = createQuestion(
        "When making decisions, you rely more on:",
        "Objective analysis", 'T',
        "Personal values", 'F',
        "Past experiences", 'S',
        "Future possibilities", 'N');
    Question *q4 = createQuestion(
        "Your daily life is usually:",
        "Well-organized", 'J',
        "Go-with-the-flow", 'P',
        "Quiet and focused", 'I',
        "Social and energetic", 'E');
    Question *q5 = createQuestion(
        "You prefer work that:",
        "Has clear instructions", 'S',
        "Allows innovation", 'N',
        "Involves logic", 'T',
        "Helps people", 'F');

    // Doubly linked list connections
    q1->next = q2;
    q2->prev = q1;
    q2->next = q3;
    q3->prev = q2;
    q3->next = q4;
    q4->prev = q3;
    q4->next = q5;
    q5->prev = q4;

    TraitNode *root = NULL;
    stack<char> history;
    Question *current = q1;
    int qNo = 1;
    char choice;

    // Quiz loop
    while (current != NULL)
    {
        cout << "\n--------------------------------------------\n";
        cout << "Question " << qNo << "\n\n";
        cout << current->text << "\n\n";
        for (int i = 0; i < 4; i++)
            cout << char('A' + i) << ") " << current->options[i] << "\n";

        cout << "\nChoice (A-D) | X = Go Back: ";
        cin >> choice;

        if (choice == 'X' || choice == 'x')
        {
            if (current->prev && !history.empty())
            {
                decrementTrait(root, history.top());
                history.pop();
                current = current->prev;
                qNo--;
            }
            else
            {
                cout << "Already at first question.\n";
            }
            continue;
        }

        int idx = choice - 'A';
        if (idx >= 0 && idx < 4)
        {
            root = insertTrait(root, current->traits[idx]);
            history.push(current->traits[idx]);
            current = current->next;
            qNo++;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    // Build MBTI type
    string type = "";
    type += (getScore(root, 'I') >= getScore(root, 'E')) ? 'I' : 'E';
    type += (getScore(root, 'S') >= getScore(root, 'N')) ? 'S' : 'N';
    type += (getScore(root, 'T') >= getScore(root, 'F')) ? 'T' : 'F';
    type += (getScore(root, 'J') >= getScore(root, 'P')) ? 'J' : 'P';

    cout << "\n============================================\n";
    cout << "Your Personality Type: " << type << endl;
    describe(type);

    // Calculate total score
    int totalScore = 0;
    totalScore += getScore(root, 'I');
    totalScore += getScore(root, 'E');
    totalScore += getScore(root, 'S');
    totalScore += getScore(root, 'N');
    totalScore += getScore(root, 'T');
    totalScore += getScore(root, 'F');
    totalScore += getScore(root, 'J');
    totalScore += getScore(root, 'P');

    return totalScore;
}

// ================= MAIN =================
int main()
{
    header();

    UserNode *leaderboard = NULL;

    while (true)
    {
        string userName;
        cout << "\nEnter your name (or type EXIT to quit): ";
        cin >> userName;

        if (userName == "EXIT" || userName == "exit")
            break;

        int score = takeQuiz();

        leaderboard = insertUser(leaderboard, userName, score);

        cout << "\nQuiz completed! You can take another quiz or type EXIT to finish.\n";
    }

    // Display final leaderboard
    cout << "\n============================================\n";
    cout << "            FINAL LEADERBOARD\n";
    cout << "============================================\n";
    displayLeaderboard(leaderboard);

    return 0;
}