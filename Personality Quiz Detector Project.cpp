#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define MAX_TYPES 8
void printSharedTraits(const string& a, const string& b);
int maxValue(int a, int b);



/*=====================================================
                    QUESTION DLL
=====================================================*/
struct Question {
    string text;
    string options[4];
    char traits[4];
    Question* next;
    Question* prev;
};

Question* createQuestion(string t,
    string o1, char c1,
    string o2, char c2,
    string o3, char c3,
    string o4, char c4)
{
    Question* q = new Question();
    q->text = t;
    q->options[0] = o1; q->traits[0] = c1;
    q->options[1] = o2; q->traits[1] = c2;
    q->options[2] = o3; q->traits[2] = c3;
    q->options[3] = o4; q->traits[3] = c4;
    q->next = q->prev = NULL;
    return q;
}

/*=====================================================
                TRAIT BST (SCORES)
=====================================================*/
struct TraitNode {
    char trait;
    int score;
    TraitNode* left;
    TraitNode* right;
};

TraitNode* createTrait(char t) {
    TraitNode* node = new TraitNode();
    node->trait = t;
    node->score = 1;
    node->left = node->right = NULL;
    return node;
}

TraitNode* insertTrait(TraitNode* root, char t) {
    if (!root) return createTrait(t);
    if (t == root->trait) root->score++;
    else if (t < root->trait) root->left = insertTrait(root->left, t);
    else root->right = insertTrait(root->right, t);
    return root;
}

void decrementTrait(TraitNode* root, char t) {
    if (!root) return;

    if (root->trait == t && root->score > 0)
        root->score--;
    else if (t < root->trait)
        decrementTrait(root->left, t);
    else
        decrementTrait(root->right, t);
}


int getScore(TraitNode* root, char t) {
    if (!root) return 0;
    if (root->trait == t) return root->score;
    if (t < root->trait) return getScore(root->left, t);
    return getScore(root->right, t);
}

/*=====================================================
                    UI
=====================================================*/
void header() {
    cout << "\n============================================\n";
    cout << "        MBTI PERSONALITY QUIZ SYSTEM\n";
    cout << "============================================\n";
    cout << "Choose A?D | X = Go Back\n";
    cout << "--------------------------------------------\n";
}

void describe(string type) {
    cout << "\n============================================\n";
    cout << "        PERSONALITY INSIGHT\n";
    cout << "============================================\n";

    if (type == "INFP") cout << "Empathetic, idealistic, creative.\n";
    else if (type == "INTJ") cout << "Strategic, analytical, independent.\n";
    else if (type == "ENTJ") cout << "Confident, decisive leader.\n";
    else if (type == "ENFP") cout << "Energetic, imaginative, inspiring.\n";
    else if (type == "ISTJ") cout << "Practical, disciplined, reliable.\n";
    else cout << "Balanced and adaptable personality.\n";
}

/*=====================================================
                AVL LEADERBOARD
=====================================================*/
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

struct UserNode {
    string name;
    int score;
    int height;
    UserNode* left;
    UserNode* right;
};

int height(UserNode* n) { return n ? n->height : 0; }

int balance(UserNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

UserNode* createUser(string name, int score) {
    UserNode* n = new UserNode();
    n->name = name;
    n->score = score;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

UserNode* rightRotate(UserNode* y) {
    UserNode* x = y->left;
    UserNode* t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = maxValue(height(y->left), height(y->right)) + 1;
    x->height = maxValue(height(x->left), height(x->right)) + 1;
    return x;
}

UserNode* leftRotate(UserNode* x) {
    UserNode* y = x->right;
    UserNode* t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = maxValue(height(x->left), height(x->right)) + 1;
    y->height = maxValue(height(y->left), height(y->right)) + 1;
    return y;
}

UserNode* insertUser(UserNode* root, string name, int score) {
    if (!root) return createUser(name, score);

    if (score > root->score)
        root->left = insertUser(root->left, name, score);
    else
        root->right = insertUser(root->right, name, score);

    root->height = maxValue(height(root->left), height(root->right)) + 1;
    int b = balance(root);

    if (b > 1 && score > root->left->score) return rightRotate(root);
    if (b < -1 && score <= root->right->score) return leftRotate(root);
    if (b > 1 && score <= root->left->score) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (b < -1 && score > root->right->score) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void showLeaderboard(UserNode* root) {
    if (!root) return;
    showLeaderboard(root->left);
    cout << root->name << " : " << root->score << endl;
    showLeaderboard(root->right);
}

/*=====================================================
            PERSONALITY GROUP BST
=====================================================*/
struct GroupNode {
    string type;
    string names[20];
    int count;
    GroupNode* left;
    GroupNode* right;
};

GroupNode* createGroup(string t, string name) {
    GroupNode* g = new GroupNode();
    g->type = t;
    g->names[0] = name;
    g->count = 1;
    g->left = g->right = NULL;
    return g;
}

GroupNode* insertGroup(GroupNode* root, string type, string name) {
    if (!root) return createGroup(type, name);

    if (type == root->type)
        root->names[root->count++] = name;
    else if (type < root->type)
        root->left = insertGroup(root->left, type, name);
    else
        root->right = insertGroup(root->right, type, name);

    return root;
}

void showGroups(GroupNode* root) {
    if (!root) return;
    showGroups(root->left);
    cout << "\n" << root->type << " Group: ";
    for (int i = 0; i < root->count; i++)
        cout << root->names[i] << "  ";
    cout << endl;
    showGroups(root->right);
}

struct AdjNode {
    int index;
    AdjNode* next;
};

struct Graph {
    string types[MAX_TYPES];
    AdjNode* adj[MAX_TYPES];
    int size;
};

int sharedLetters(const string& a, const string& b) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (a[i] == b[i])
            count++;
    }
    return count;
}

void addEdge(Graph& g, int u, int v) {
    AdjNode* node1 = new AdjNode();
    node1->index = v;
    node1->next = g.adj[u];
    g.adj[u] = node1;

    AdjNode* node2 = new AdjNode();
    node2->index = u;
    node2->next = g.adj[v];
    g.adj[v] = node2;
}

Graph buildPersonalityGraph() {
    Graph g;
    g.size = MAX_TYPES;

    string temp[MAX_TYPES] = {
        "INFP", "ENFP", "INFJ", "ENFJ",
        "INTJ", "ENTJ", "ISFP", "ESFP"
    };

    for (int i = 0; i < MAX_TYPES; i++) {
        g.types[i] = temp[i];
        g.adj[i] = NULL;
    }

    for (int i = 0; i < MAX_TYPES; i++) {
        for (int j = i + 1; j < MAX_TYPES; j++) {
            if (sharedLetters(g.types[i], g.types[j]) >= 2) {
                addEdge(g, i, j);
            }
        }
    }
    return g;
}

void showSimilarPersonalities(Graph& g, const string& userType) {
    int start = -1;

    for (int i = 0; i < g.size; i++) {
        if (g.types[i] == userType) {
            start = i;
            break;
        }
    }

    if (start == -1) {
        cout << "\nNo personality map available.\n";
        return;
    }

    bool visited[MAX_TYPES] = {false};
    int queue[MAX_TYPES];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    cout << "\n==============================================\n";
    cout << "        YOUR PERSONALITY MAP\n";
    cout << "==============================================\n";
    cout << "\nYou are: " << userType << "\n\n";

    cout << "Closest Personality Matches:\n";
    cout << "----------------------------------------------\n";

    bool firstLayer = true;

    while (front < rear) {
        int u = queue[front++];

        AdjNode* temp = g.adj[u];
        while (temp != NULL) {
            int v = temp->index;

            if (!visited[v]) {
                visited[v] = true;

                int common = sharedLetters(userType, g.types[v]);

                if (common >= 3) {
                    cout << "? " << g.types[v];
                    printSharedTraits(userType, g.types[v]);
                    cout << endl;
                }

                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    cout << "\nRelated but Less Similar:\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < g.size; i++) {
        if (g.types[i] != userType && sharedLetters(userType, g.types[i]) == 2) {
            cout << "• " << g.types[i] << endl;
        }
    }

    cout << "\n==============================================\n";
}

void printSharedTraits(const string& a, const string& b) {
    cout << " (Shares: ";
    bool first = true;
    for (int i = 0; i < 4; i++) {
        if (a[i] == b[i]) {
            if (!first) cout << " ";
            cout << a[i];
            first = false;
        }
    }
    cout << ")";
}


/*=====================================================
                QUIZ ENGINE
=====================================================*/
int takeQuiz(string& personality) {

    Question* q1 = createQuestion(
        "You prefer tasks that are:",
        "Creative and open-ended", 'N',
        "Logical and structured", 'T',
        "People-focused", 'F',
        "Routine-based", 'S'
    );

    Question* q2 = createQuestion(
        "You usually think about:",
        "Future possibilities", 'N',
        "Practical details", 'S',
        "Logic", 'T',
        "Emotions", 'F'
    );

    Question* q3 = createQuestion(
        "You work best when:",
        "Planning", 'J',
        "Adapting", 'P',
        "Leading", 'E',
        "Working alone", 'I'
    );

    Question* q4 = createQuestion(
        "You prefer decisions that are:",
        "Logical", 'T',
        "Value-based", 'F',
        "Fast", 'J',
        "Flexible", 'P'
    );

    Question* q5 = createQuestion(
        "You recharge by:",
        "Being alone", 'I',
        "Socializing", 'E',
        "Organizing", 'J',
        "Exploring", 'P'
    );

    q1->next = q2;
    q2->prev = q1; q2->next = q3;
    q3->prev = q2; q3->next = q4;
    q4->prev = q3; q4->next = q5;
    q5->prev = q4;

    TraitNode* root = NULL;
    stack<char> history;
    Question* current = q1;
    char choice;
    int qNo = 1;

    while (current) {
        cout << "\nQuestion " << qNo << "\n" << current->text << "\n";
        for (int i = 0; i < 4; i++)
            cout << char('A' + i) << ") " << current->options[i] << endl;

        cout << "Choice: ";
        cin >> choice;


if (choice >= 'a' && choice <= 'z') {
    choice = choice - 'a' + 'A';
}


       if ((choice == 'X' || choice == 'x')) {
    if (!history.empty() && current->prev != NULL) {
        decrementTrait(root, history.top());
        history.pop();
        current = current->prev;
        continue;
    } else {
        cout << "\n?? Cannot undo further.\n";
        continue;
    }
}

	if (choice < 'A' || choice > 'D') {
    cout << "Invalid choice. Please select A-D.\n";
    continue;
}

        int idx = choice - 'A';
        if (idx >= 0 && idx < 4) {
            root = insertTrait(root, current->traits[idx]);
            history.push(current->traits[idx]);
            current = current->next;
            qNo++;
        }
    }

    personality = "";
    personality += (getScore(root, 'I') >= getScore(root, 'E')) ? 'I' : 'E';
    personality += (getScore(root, 'S') >= getScore(root, 'N')) ? 'S' : 'N';
    personality += (getScore(root, 'T') >= getScore(root, 'F')) ? 'T' : 'F';
    personality += (getScore(root, 'J') >= getScore(root, 'P')) ? 'J' : 'P';

    describe(personality);

    int totalScore =
        getScore(root, 'N') * 2 +
        getScore(root, 'T') * 2 +
        getScore(root, 'J') * 2 +
        getScore(root, 'E') +
        getScore(root, 'F') +
        getScore(root, 'S') +
        getScore(root, 'P') +
        getScore(root, 'I');

    return totalScore;
}

/*=====================================================
                    MAIN
=====================================================*/
int main() {
    header();
    Graph g = buildPersonalityGraph();


    UserNode* leaderboard = NULL;
    GroupNode* groups = NULL;
    string lastPersonality = "";

    while (true) {
        string name;
        cout << "\nEnter your name (or if you want to EXIT type bye): ";
        cin >> name;

        if (name == "bye") break;

        string personality;
        int score = takeQuiz(personality);

        lastPersonality = personality;

        leaderboard = insertUser(leaderboard, name, score);
        groups = insertGroup(groups, personality, name);
        cout << "\nYour Personality Type: " << personality << endl;

		showSimilarPersonalities(g, personality);
		

        cout << "\nQuiz Completed!\n";
    }

    cout << "\n================ LEADERBOARD ================\n";
    showLeaderboard(leaderboard);

    cout << "\n============ PERSONALITY GROUPS =============\n";
    showGroups(groups);


    return 0;
}
