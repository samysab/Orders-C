// prototypes fenetres
void firstWindow();
void Windowscommande();
void adminLoginWindow();
void newOrder();
void login_connect(GtkWidget*, GtkWidget**);

void OnDestroy(GtkWidget *pWidget, void* pData);
void loadTypes(GtkWidget *pWidget, void**);
void browseList(product_t *);
void addList(product_t*, int, char name[50], char image_path[50], int);
void addTypesList(GtkWidget *btn, void** data);
void orderWindow(GtkWidget*, void**);
void removeProduct(GtkWidget*, void**);



int currentIsInRecap(char name[50], sum_t *list);
void addRecap(sum_t **head, char name[20], int nb, int id, int price);
sum_t* sum(product_t *head);
int insertInOrders(int productId, int orderId, char name[50]);
int insertOrder(sum_t *head, char comment[255]);
void confirmOrder (GtkWidget *btn, void* infos[3]);


void draw_line_vertical_price(HPDF_Page page, float x, float y);
void draw_line_vertical(HPDF_Page page, float x, float y);
void draw_line_horizontal_price(HPDF_Page page, float x, float y);
void draw_line_horizontal(HPDF_Page page, float x, float y);
void draw_image (HPDF_Doc pdf, const char *filename, float x, float y);
void pdgPage(char** tableau2d, sum_t *head, char comment[250]);

char** configuration();
