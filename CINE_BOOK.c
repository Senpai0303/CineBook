/**
 * CineBook: Efficient Movie Ticket Booking System Using Data Structures
 * Developed by ShowTime Innovators:
 * - Divyansh Joshi (Team Lead)
 * - Priyanshi Thapa
 * - Dipika Parmar
 * - Priyanka Takuli
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <ctype.h>

 #define MAX_NAME 50
 #define MAX_DESC 200
 #define MAX_ROWS 10
 #define MAX_COLS 20
 #define MAX_SEATS (MAX_ROWS * MAX_COLS)
 #define MAX_MOVIES 10
 #define MAX_SHOWTIMES 5
 #define MAX_BOOKINGS 100
 #define MAX_CUSTOMERS 50
 #define ADMIN_PASSWORD "admin123"

 typedef struct Movie Movie;
 typedef struct Showtime Showtime;
 typedef struct Booking Booking;
 typedef struct Customer Customer;
 typedef struct MovieNode MovieNode;
 typedef struct ShowtimeNode ShowtimeNode;

 struct Movie {
     int id;
     char name[MAX_NAME];
     char genre[MAX_NAME];
     char description[MAX_DESC];
     int duration;
     float base_price;
 };

 struct Showtime {
     int id;
     int movie_id;
     char time[MAX_NAME];
     char date[MAX_NAME];
     int seats[MAX_ROWS][MAX_COLS];
     float price;
     int hall_number;
 };

 struct Booking {
     int id;
     int customer_id;
     int showtime_id;
     int movie_id;
     int row;
     int col;
     char booking_time[MAX_NAME];
     float amount;
 };

 struct Customer {
     int id;
     char name[MAX_NAME];
     char phone[MAX_NAME];
     char email[MAX_NAME];
 };

 struct MovieNode {
     Movie movie;
     MovieNode* next;
 };

 struct ShowtimeNode {
     Showtime showtime;
     ShowtimeNode* next;
 };

 MovieNode* movie_list = NULL;
 ShowtimeNode* showtime_list = NULL;
 Booking bookings[MAX_BOOKINGS];
 Customer customers[MAX_CUSTOMERS];

 int movie_count = 0;
 int showtime_count = 0;
 int booking_count = 0;
 int customer_count = 0;

 
 MovieNode* create_movie_node(Movie movie);
 void add_movie(Movie movie);
 void list_all_movies();
 Movie* find_movie_by_id(int id);
 void edit_movie(int id);
 void delete_movie(int id);

 ShowtimeNode* create_showtime_node(Showtime showtime);
 void add_showtime(Showtime showtime);
 void list_movie_showtimes(int movie_id);
 Showtime* find_showtime_by_id(int id);
 void initialize_seats(Showtime* showtime);
 void display_seats(Showtime* showtime);

 int add_booking(Booking booking);
 void list_customer_bookings(int customer_id);
 Booking* find_booking_by_id(int id);
 void cancel_booking(int id);
 void generate_ticket(Booking* booking);

 int add_customer(Customer customer);
 Customer* find_customer_by_id(int id);
 Customer* find_customer_by_phone(char* phone);

 void clear_screen();
 void display_header();
 int generate_id(char* entity);
 void get_current_datetime(char* datetime);
 void initialize_system();
 void load_demo_data();

 void main_menu();
 void admin_menu();
 void customer_menu();
 void booking_menu();
 void movie_management_menu();
 void showtime_management_menu();


 MovieNode* create_movie_node(Movie movie) {
     MovieNode* node = (MovieNode*)malloc(sizeof(MovieNode));
     if (!node) {
         printf("Memory allocation failed\n");
         exit(1);
     }
     node->movie = movie;
     node->next = NULL;
     return node;
 }

 void add_movie(Movie movie) {
     MovieNode* node = create_movie_node(movie);
     if (movie_list == NULL) {
         movie_list = node;
     } else {
         MovieNode* temp = movie_list;
         while (temp->next != NULL) {
             temp = temp->next;
         }
         temp->next = node;
     }
     movie_count++;
 }

 void list_all_movies() {
     if (movie_list == NULL) {
         printf("No movies available\n");
         return;
     }
     printf("\n%-5s | %-30s | %-15s | %-10s | %-12s\n", "ID", "Title", "Genre", "Duration", "Base Price");
     printf("-------------------------------------------------------------------------\n");
     MovieNode* temp = movie_list;
     while (temp != NULL) {
         printf("%-5d | %-30s | %-15s | %d mins  | Rs.%.2f\n",
                temp->movie.id,
                temp->movie.name,
                temp->movie.genre,
                temp->movie.duration,
                temp->movie.base_price);
         temp = temp->next;
     }
     printf("\n");
 }

 Movie* find_movie_by_id(int id) {
     MovieNode* temp = movie_list;
     while (temp != NULL) {
         if (temp->movie.id == id) {
             return &(temp->movie);
         }
         temp = temp->next;
     }
     return NULL;
 }

 void edit_movie(int id) {
     Movie* movie = find_movie_by_id(id);
     if (movie == NULL) {
         printf("Movie not found\n");
         return;
     }
     printf("\nEditing movie: %s\n", movie->name);
     printf("Enter new name (or press enter to keep current): ");
     char input[MAX_NAME];
     fgets(input, MAX_NAME, stdin);
     input[strcspn(input, "\n")] = 0;
     if (strlen(input) > 0) {
         strcpy(movie->name, input);
     }
     printf("Enter new genre (or press enter to keep current): ");
     fgets(input, MAX_NAME, stdin);
     input[strcspn(input, "\n")] = 0;
     if (strlen(input) > 0) {
         strcpy(movie->genre, input);
     }
     printf("Enter new description (or press enter to keep current): ");
     fgets(input, MAX_DESC, stdin);
     input[strcspn(input, "\n")] = 0;
     if (strlen(input) > 0) {
         strcpy(movie->description, input);
     }
     printf("Enter new duration in minutes (or press enter to keep current): ");
     fgets(input, MAX_NAME, stdin);
     input[strcspn(input, "\n")] = 0;
     if (strlen(input) > 0) {
         movie->duration = atoi(input);
     }
     printf("Movie updated successfully\n");
 }

 void delete_movie(int id) {
     if (movie_list == NULL) {
         printf("No movies available\n");
         return;
     }
     if (movie_list->movie.id == id) {
         MovieNode* temp = movie_list;
         movie_list = movie_list->next;
         free(temp);
         movie_count--;
         printf("Movie deleted successfully\n");
         return;
     }
     MovieNode* prev = movie_list;
     MovieNode* current = movie_list->next;
     while (current != NULL) {
         if (current->movie.id == id) {
             prev->next = current->next;
             free(current);
             movie_count--;
             printf("Movie deleted successfully\n");
             return;
         }
         prev = current;
         current = current->next;
     }
     printf("Movie not found\n");
 }

 ShowtimeNode* create_showtime_node(Showtime showtime) {
     ShowtimeNode* node = (ShowtimeNode*)malloc(sizeof(ShowtimeNode));
     if (!node) {
         printf("Memory allocation failed\n");
         exit(1);
     }
     node->showtime = showtime;
     node->next = NULL;
     return node;
 }

 void add_showtime(Showtime showtime) {
     ShowtimeNode* node = create_showtime_node(showtime);
     if (showtime_list == NULL) {
         showtime_list = node;
     } else {
         ShowtimeNode* temp = showtime_list;
         while (temp->next != NULL) {
             temp = temp->next;
         }
         temp->next = node;
     }
     showtime_count++;
 }

 void list_movie_showtimes(int movie_id) {
     if (showtime_list == NULL) {
         printf("No showtimes available\n");
         return;
     }
     Movie* movie = find_movie_by_id(movie_id);
     if (movie == NULL) {
         printf("Movie not found\n");
         return;
     }
     printf("\nShowtimes for '%s':\n", movie->name);
     printf("%-5s | %-12s | %-12s | %-8s | %-10s\n", "ID", "Date", "Time", "Hall", "Price");
     printf("----------------------------------------------------\n");
     ShowtimeNode* temp = showtime_list;
     int found = 0;
     while (temp != NULL) {
         if (temp->showtime.movie_id == movie_id) {
             printf("%-5d | %-12s | %-12s | %-8d | Rs.%.2f\n",
                    temp->showtime.id,
                    temp->showtime.date,
                    temp->showtime.time,
                    temp->showtime.hall_number,
                    temp->showtime.price);
             found = 1;
         }
         temp = temp->next;
     }
     if (!found) {
         printf("No showtimes available for this movie\n");
     }
     printf("\n");
 }

 Showtime* find_showtime_by_id(int id) {
     ShowtimeNode* temp = showtime_list;
     while (temp != NULL) {
         if (temp->showtime.id == id) {
             return &(temp->showtime);
         }
         temp = temp->next;
     }
     return NULL;
 }

 void initialize_seats(Showtime* showtime) {
     for (int i = 0; i < MAX_ROWS; i++) {
         for (int j = 0; j < MAX_COLS; j++) {
             showtime->seats[i][j] = 0;
         }
     }
 }

 void display_seats(Showtime* showtime) {
     if (showtime == NULL) {
         printf("Invalid showtime\n");
         return;
     }
     Movie* movie = find_movie_by_id(showtime->movie_id);
     if (movie == NULL) {
         printf("Movie information not available\n");
         return;
     }
     printf("\n=== Seating for %s - %s %s ===\n",
            movie->name, showtime->date, showtime->time);
     printf("Ticket Price: Rs.%.2f\n\n", showtime->price);
     printf("         SCREEN\n");
     printf("-------------------------\n\n");
     printf("   ");
     for (int j = 0; j < MAX_COLS; j++) {
         printf("%2d ", j+1);
     }
     printf("\n");
     for (int i = 0; i < MAX_ROWS; i++) {
         printf("%c  ", 'A' + i);
         for (int j = 0; j < MAX_COLS; j++) {
             if (showtime->seats[i][j] == 0) {
                 printf("[ ]");
             } else {
                 printf("[X]");
             }
         }
         printf("\n");
     }
     printf("\n[ ] - Available    [X] - Booked\n\n");
 }

 int add_booking(Booking booking) {
     if (booking_count >= MAX_BOOKINGS) {
         printf("Maximum bookings reached\n");
         return 0;
     }
     Showtime* showtime = find_showtime_by_id(booking.showtime_id);
     if (!showtime) {
         printf("Invalid showtime\n");
         return 0;
     }
     if (booking.row < 0 || booking.row >= MAX_ROWS ||
         booking.col < 0 || booking.col >= MAX_COLS) {
         printf("Invalid seat selection\n");
         return 0;
     }
     if (showtime->seats[booking.row][booking.col] != 0) {
         printf("Seat already booked\n");
         return 0;
     }
     showtime->seats[booking.row][booking.col] = 1;
     bookings[booking_count] = booking;
     booking_count++;
     return 1;
 }

 void list_customer_bookings(int customer_id) {
     int found = 0;
     printf("\n=== Your Bookings ===\n\n");
     printf("%-5s | %-20s | %-12s | %-12s | %-10s | %-10s\n",
            "ID", "Movie", "Date", "Time", "Seat", "Amount");
     printf("----------------------------------------------------------------------\n");
     for (int i = 0; i < booking_count; i++) {
         if (bookings[i].customer_id == customer_id) {
             Movie* movie = find_movie_by_id(bookings[i].movie_id);
             Showtime* showtime = find_showtime_by_id(bookings[i].showtime_id);
             if (movie && showtime) {
                 char seat[5];
                 sprintf(seat, "%c%d", 'A' + bookings[i].row, bookings[i].col + 1);
                 printf("%-5d | %-20s | %-12s | %-12s | %-10s | Rs.%-9.2f\n",
                        bookings[i].id,
                        movie->name,
                        showtime->date,
                        showtime->time,
                        seat,
                        bookings[i].amount);
                 found = 1;
             }
         }
     }
     if (!found) {
         printf("No bookings found\n");
     }
     printf("\n");
 }

 Booking* find_booking_by_id(int id) {
     for (int i = 0; i < booking_count; i++) {
         if (bookings[i].id == id) {
             return &bookings[i];
         }
     }
     return NULL;
 }

 void cancel_booking(int id) {
     Booking* booking = find_booking_by_id(id);
     if (!booking) {
         printf("Booking not found\n");
         return;
     }
     Showtime* showtime = find_showtime_by_id(booking->showtime_id);
     if (showtime) {
         showtime->seats[booking->row][booking->col] = 0;
     }
     *booking = bookings[booking_count - 1];
     booking_count--;
     printf("Booking cancelled successfully\n");
 }

 void generate_ticket(Booking* booking) {
     if (!booking) {
         printf("Invalid booking\n");
         return;
     }
     Movie* movie = find_movie_by_id(booking->movie_id);
     Showtime* showtime = find_showtime_by_id(booking->showtime_id);
     Customer* customer = find_customer_by_id(booking->customer_id);
     if (!movie || !showtime || !customer) {
         printf("Unable to generate ticket - missing information\n");
         return;
     }
     clear_screen();
     printf("\n");
     printf("=========================================\n");
     printf("             CINE BOOK TICKET            \n");
     printf("=========================================\n");
     printf("Ticket ID: #%d\n", booking->id);
     printf("Booking Time: %s\n", booking->booking_time);
     printf("-----------------------------------------\n");
     printf("Movie: %s\n", movie->name);
     printf("Date: %s\n", showtime->date);
     printf("Time: %s\n", showtime->time);
     printf("Hall: %d\n", showtime->hall_number);
     printf("Seat: %c%d\n", 'A' + booking->row, booking->col + 1);
     printf("-----------------------------------------\n");
     printf("Customer: %s\n", customer->name);
     printf("Phone: %s\n", customer->phone);
     printf("-----------------------------------------\n");
     printf("Amount Paid: Rs.%.2f\n", booking->amount);
     printf("=========================================\n");
     printf(" Thank you for choosing CineBook! Enjoy! \n");
     printf("=========================================\n\n");
 }

 int add_customer(Customer customer) {
     if (customer_count >= MAX_CUSTOMERS) {
         printf("Maximum customers reached\n");
         return -1;
     }
     for (int i = 0; i < customer_count; i++) {
         if (strcmp(customers[i].phone, customer.phone) == 0) {
             return customers[i].id;
         }
     }
     customers[customer_count] = customer;
     customer_count++;
     return customer.id;
 }

 Customer* find_customer_by_id(int id) {
     for (int i = 0; i < customer_count; i++) {
         if (customers[i].id == id) {
             return &customers[i];
         }
     }
     return NULL;
 }

 Customer* find_customer_by_phone(char* phone) {
     for (int i = 0; i < customer_count; i++) {
         if (strcmp(customers[i].phone, phone) == 0) {
             return &customers[i];
         }
     }
     return NULL;
 }

 void clear_screen() {
     #ifdef _WIN32
         system("cls");
     #else
         system("clear");
     #endif
 }

 void display_header() {
     printf("\n");
     printf("===========================================\n");
     printf("||                                       ||\n");
     printf("||          CINE BOOK SYSTEM             ||\n");
     printf("||                                       ||\n");
     printf("===========================================\n");
 }

 int generate_id(char* entity) {
     static int movie_id = 1000;
     static int showtime_id = 2000;
     static int booking_id = 3000;
     static int customer_id = 4000;

     if (strcmp(entity, "movie") == 0) return movie_id++;
     if (strcmp(entity, "showtime") == 0) return showtime_id++;
     if (strcmp(entity, "booking") == 0) return booking_id++;
     if (strcmp(entity, "customer") == 0) return customer_id++;
     return -1;
 }

 void get_current_datetime(char* datetime) {
     time_t now;
     struct tm *local_time;
     time(&now);
     local_time = localtime(&now);
     strftime(datetime, MAX_NAME, "%Y-%m-%d %H:%M", local_time);
 }

 void initialize_system() {
     movie_list = NULL;
     showtime_list = NULL;
     movie_count = 0;
     showtime_count = 0;
     booking_count = 0;
     customer_count = 0;
     load_demo_data();
 }

 void load_demo_data() {
     Movie movies[] = {
         {generate_id("movie"), "Avengers: Endgame", "Action/Sci-Fi",
          "The Avengers take a final stand against Thanos.", 181, 250.0},
         {generate_id("movie"), "The Shawshank Redemption", "Drama",
          "Two imprisoned men bond over a number of years.", 142, 200.0}
     };
     for (int i = 0; i < 2; i++) { 
         add_movie(movies[i]);
     }

     char dates[][MAX_NAME] = {"2025-04-15", "2025-04-16"}; 
     char times[][MAX_NAME] = {"10:00 AM", "1:30 PM"}; 

     for (int movie_idx = 0; movie_idx < 2; movie_idx++) {
         for (int date_idx = 0; date_idx < 1; date_idx++) { 
             for (int time_idx = 0; time_idx < 1; time_idx++) {
                 Showtime showtime;
                 showtime.id = generate_id("showtime");
                 showtime.movie_id = movies[movie_idx].id;
                 strcpy(showtime.date, dates[date_idx]);
                 strcpy(showtime.time, times[time_idx]);
                 showtime.price = movies[movie_idx].base_price; 
                 showtime.hall_number = 1; 
                 initialize_seats(&showtime);
                 
                 for (int k = 0; k < 2; k++) {
                     int row = rand() % MAX_ROWS;
                     int col = rand() % MAX_COLS;
                     showtime.seats[row][col] = 1;
                 }
                 add_showtime(showtime);
             }
         }
     }

     Customer customer;
     customer.id = generate_id("customer");
     strcpy(customer.name, "John Doe");
     strcpy(customer.phone, "9876543210");
     strcpy(customer.email, "john@example.com");
     add_customer(customer);
 }

 void movie_management_menu() {
     int choice;
     do {
         clear_screen();
         display_header();
         printf("\n=== MOVIE MANAGEMENT ===\n\n");
         printf("1. Add New Movie\n");
         printf("2. View All Movies\n");
         printf("3. Edit Movie\n");
         printf("4. Return to Admin Menu\n"); 
         printf("\nEnter your choice: ");
         scanf("%d", &choice);
         while(getchar() != '\n');
         switch(choice) {
             case 1: {
                 Movie movie;
                 movie.id = generate_id("movie");
                 printf("Enter movie name: ");
                 fgets(movie.name, MAX_NAME, stdin);
                 movie.name[strcspn(movie.name, "\n")] = 0;
                 printf("Enter genre: ");
                 fgets(movie.genre, MAX_NAME, stdin);
                 movie.genre[strcspn(movie.genre, "\n")] = 0;
                 printf("Enter description: ");
                 fgets(movie.description, MAX_DESC, stdin);
                 movie.description[strcspn(movie.description, "\n")] = 0;
                 printf("Enter duration (minutes): ");
                 scanf("%d", &movie.duration);
                 printf("Enter base ticket price (Rs.): ");
                 scanf("%f", &movie.base_price);
                 while(getchar() != '\n');
                 add_movie(movie);
                 printf("Movie added successfully!\n");
                 printf("Press enter to continue...");
                 getchar();
                 break;
             }
             case 2:
                 list_all_movies();
                 printf("Press enter to continue...");
                 getchar();
                 break;
             case 3: {
                 list_all_movies();
                 printf("Enter movie ID to edit (0 to cancel): ");
                 int movie_id;
                 scanf("%d", &movie_id);
                 while(getchar() != '\n');
                 if (movie_id != 0) {
                     edit_movie(movie_id);
                 }
                 printf("Press enter to continue...");
                 getchar();
                 break;
             }
             case 4: 
                 break;
             default:
                 printf("Invalid choice! Press enter to continue...");
                 getchar();
         }
     } while(choice != 4); 
 }

 void showtime_management_menu() {
     int choice;
     do {
         clear_screen();
         display_header();
         printf("\n=== SHOWTIME MANAGEMENT ===\n\n");
         printf("1. Add New Showtime\n");
         printf("2. View Movie Showtimes\n");
         printf("3. Return to Admin Menu\n"); 
         printf("\nEnter your choice: ");
         scanf("%d", &choice);
         while(getchar() != '\n');
         switch(choice) {
             case 1: {
                 list_all_movies();
                 printf("Enter movie ID for showtime: ");
                 int movie_id;
                 scanf("%d", &movie_id);
                 while(getchar() != '\n');
                 Movie* movie = find_movie_by_id(movie_id);
                 if (!movie) {
                     printf("Movie not found!\n");
                     printf("Press enter to continue...");
                     getchar();
                     break;
                 }
                 Showtime showtime;
                 showtime.id = generate_id("showtime");
                 showtime.movie_id = movie_id;
                 printf("Enter date (YYYY-MM-DD): ");
                 fgets(showtime.date, MAX_NAME, stdin);
                 showtime.date[strcspn(showtime.date, "\n")] = 0;
                 printf("Enter time (HH:MM AM/PM): ");
                 fgets(showtime.time, MAX_NAME, stdin);
                 showtime.time[strcspn(showtime.time, "\n")] = 0;
                 printf("Enter hall number: ");
                 scanf("%d", &showtime.hall_number);
                 showtime.price = movie->base_price; 
                 while(getchar() != '\n');
                 initialize_seats(&showtime);
                 add_showtime(showtime);
                 printf("Showtime added successfully!\n");
                 printf("Press enter to continue...");
                 getchar();
                 break;
             }
             case 2: {
                 list_all_movies();
                 printf("Enter movie ID to view showtimes: ");
                 int movie_id;
                 scanf("%d", &movie_id);
                 while(getchar() != '\n');
                 list_movie_showtimes(movie_id);
                 printf("Press enter to continue...");
                 getchar();
                 break;
             }
             case 3: 
                 break;
             default:
                 printf("Invalid choice! Press enter to continue...");
                 getchar();
         }
     } while(choice != 3); 
 }

 void admin_menu() {
     char password[MAX_NAME];
     printf("Enter admin password: ");
     fgets(password, MAX_NAME, stdin);
     password[strcspn(password, "\n")] = 0;
     if (strcmp(password, ADMIN_PASSWORD) != 0) {
         printf("Invalid password!\n");
         printf("Press enter to continue...");
         getchar();
         return;
     }

     int choice;
     do {
         clear_screen();
         display_header();
         printf("\n=== ADMIN PANEL ===\n\n");
         printf("1. Movie Management\n");
         printf("2. Showtime Management\n");
         printf("3. Return to Main Menu\n"); 
         printf("\nEnter your choice: ");
         scanf("%d", &choice);
         while(getchar() != '\n');
         switch(choice) {
             case 1:
                 movie_management_menu();
                 break;
             case 2:
                 showtime_management_menu();
                 break;
             case 3: 
                 break;
             default:
                 printf("Invalid choice! Press enter to continue...");
                 getchar();
         }
     } while(choice != 3); 
 }

 void booking_menu() {
     int choice;
     static int current_customer_id = -1;
     do {
         clear_screen();
         display_header();
         if (current_customer_id == -1) {
             printf("\n=== CUSTOMER LOGIN/REGISTER ===\n\n");
             printf("1. Login with Phone Number\n");
             printf("2. Register New Customer\n");
             printf("3. Return to Main Menu\n");
             printf("\nEnter your choice: ");
             scanf("%d", &choice);
             while(getchar() != '\n');
             switch(choice) {
                 case 1: {
                     printf("Enter your phone number: ");
                     char phone[MAX_NAME];
                     fgets(phone, MAX_NAME, stdin);
                     phone[strcspn(phone, "\n")] = 0;
                     Customer* customer = find_customer_by_phone(phone);
                     if (customer) {
                         current_customer_id = customer->id;
                         printf("Welcome back, %s!\n", customer->name);
                         printf("Press enter to continue...");
                         getchar();
                     } else {
                         printf("Phone number not found. Please register first.\n");
                         printf("Press enter to continue...");
                         getchar();
                     }
                     break;
                 }
                 case 2: {
                     Customer customer;
                     customer.id = generate_id("customer");
                     printf("Enter your name: ");
                     fgets(customer.name, MAX_NAME, stdin);
                     customer.name[strcspn(customer.name, "\n")] = 0;
                     printf("Enter your phone number: ");
                     fgets(customer.phone, MAX_NAME, stdin);
                     customer.phone[strcspn(customer.phone, "\n")] = 0;
                     printf("Enter your email: ");
                     fgets(customer.email, MAX_NAME, stdin);
                     customer.email[strcspn(customer.email, "\n")] = 0;
                     int result = add_customer(customer);
                     if (result != -1) {
                         current_customer_id = customer.id;
                         printf("Registration successful! Welcome, %s!\n", customer.name);
                         printf("Press enter to continue...");
                         getchar();
                     } else {
                         printf("Registration failed. Please try again.\n");
                         printf("Press enter to continue...");
                         getchar();
                     }
                     break;
                 }
                 case 3:
                     return;
                 default:
                     printf("Invalid choice! Press enter to continue...");
                     getchar();
             }
         } else {
             Customer* customer = find_customer_by_id(current_customer_id);
             printf("\n=== BOOKING MENU ===\n");
             printf("Welcome, %s!\n\n", customer ? customer->name : "Customer");
             printf("1. Browse Movies\n");
             printf("2. Book Ticket\n");
             printf("3. View My Bookings\n");
             printf("4. Logout\n"); 
             printf("\nEnter your choice: ");
             scanf("%d", &choice);
             while(getchar() != '\n');
             switch(choice) {
                 case 1:
                     list_all_movies(); 
                     printf("Press enter to continue...");
                     getchar();
                     break;
                 case 2: {
                     list_all_movies(); 
                     printf("Enter movie ID to book: ");
                     int movie_id;
                     scanf("%d", &movie_id);
                     while(getchar() != '\n');
                     Movie* movie = find_movie_by_id(movie_id);
                     if (!movie) {
                         printf("Movie not found!\n");
                         printf("Press enter to continue...");
                         getchar();
                         break;
                     }
                     list_movie_showtimes(movie_id);
                     printf("Enter showtime ID: ");
                     int showtime_id;
                     scanf("%d", &showtime_id);
                     while(getchar() != '\n');
                     Showtime* showtime = find_showtime_by_id(showtime_id);
                     if (!showtime) {
                         printf("Showtime not found!\n");
                         printf("Press enter to continue...");
                         getchar();
                         break;
                     }
                     display_seats(showtime);
                     printf("Enter seat row (A-J): ");
                     char row_char;
                     scanf(" %c", &row_char);
                     printf("Enter seat number (1-%d): ", MAX_COLS);
                     int col_num;
                     scanf("%d", &col_num);
                     while(getchar() != '\n');
                     int row = toupper(row_char) - 'A';
                     int col = col_num - 1;
                     if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS) {
                         printf("Invalid seat selection!\n");
                         printf("Press enter to continue...");
                         getchar();
                         break;
                     }
                     Booking booking;
                     booking.id = generate_id("booking");
                     booking.customer_id = current_customer_id;
                     booking.showtime_id = showtime_id;
                     booking.movie_id = movie_id;
                     booking.row = row;
                     booking.col = col;
                     booking.amount = showtime->price;
                     get_current_datetime(booking.booking_time);
                     if (add_booking(booking)) {
                         printf("\nBooking successful!\n");
                         printf("Ticket Price: Rs.%.2f\n\n", booking.amount);
                         printf("Generating ticket...\n");
                         printf("Press enter to view ticket...");
                         getchar();
                         Booking* saved_booking = find_booking_by_id(booking.id);
                         if (saved_booking) {
                             generate_ticket(saved_booking);
                         }
                         printf("Press enter to continue...");
                         getchar();
                     } else {
                         printf("Booking failed!\n");
                         printf("Press enter to continue...");
                         getchar();
                     }
                     break;
                 }
                 case 3:
                     list_customer_bookings(current_customer_id);
                     printf("Press enter to continue...");
                     getchar();
                     break;
                 case 4: 
                     current_customer_id = -1;
                     printf("Logged out successfully!\n");
                     printf("Press enter to continue...");
                     getchar();
                     break;
                 default:
                     printf("Invalid choice! Press enter to continue...");
                     getchar();
             }
         }
     } while(choice != 3 && choice != 4); 
 }

 void customer_menu() {
     int choice;
     do {
         clear_screen();
         display_header();
         printf("\n=== CUSTOMER PORTAL ===\n\n");
         printf("1. Browse Movies\n");
         printf("2. Book Tickets\n");
         printf("3. Return to Main Menu\n");
         printf("\nEnter your choice: ");
         scanf("%d", &choice);
         while(getchar() != '\n');
         switch(choice) {
             case 1:
                 list_all_movies(); 
                 printf("Press enter to continue...");
                 getchar();
                 break;
             case 2:
                 booking_menu();
                 break;
             case 3:
                 break;
             default:
                 printf("Invalid choice! Press enter to continue...");
                 getchar();
         }
     } while(choice != 3);
 }

 void main_menu() {
     int choice;
     do {
         clear_screen();
         display_header();
         printf("\n=== MAIN MENU ===\n\n");
         printf("1. Customer Portal\n");
         printf("2. Admin Panel\n");
         printf("3. Exit\n");
         printf("\nEnter your choice: ");
         scanf("%d", &choice);
         while(getchar() != '\n');
         switch(choice) {
             case 1:
                 customer_menu();
                 break;
             case 2:
                 admin_menu();
                 break;
             case 3:
                 printf("\nThank you for using CineBook!\n");
                 
                 break;
             default:
                 printf("Invalid choice! Press enter to continue...");
                 getchar();
         }
     } while(choice != 3);
 }

 int main() {
     printf("Initializing CineBook System...\n");
     initialize_system();
     printf("System initialized successfully!\n");
     printf("Press enter to continue...");
     getchar();
     main_menu();

     
     MovieNode* movie_temp = movie_list;
     while (movie_temp != NULL) {
         MovieNode* next = movie_temp->next;
         free(movie_temp);
         movie_temp = next;
     }

     ShowtimeNode* showtime_temp = showtime_list;
     while (showtime_temp != NULL) {
         ShowtimeNode* next = showtime_temp->next;
         free(showtime_temp);
         showtime_temp = next;
     }

     return 0;
 }
