# CineBook: Efficient Movie Ticket Booking System

**A comprehensive movie ticket booking system implemented in C using advanced data structures**

## 🎬 Project Overview

CineBook is a feature-rich movie ticket booking system developed by **ShowTime Innovators** team. The system efficiently manages movie listings, showtimes, customer bookings, and administrative operations using linked lists and arrays as core data structures.

### 👥 Development Team
- **Divyansh Joshi** - Team Lead
- **Priyanshi Thapa** - Developer
- **Dipika Parmar** - Developer
- **Priyanka Takuli** - Developer

## ✨ Key Features

### 🎭 Customer Features
- **User Registration & Login** - Phone-based authentication system
- **Movie Browsing** - View all available movies with pricing information
- **Interactive Seat Selection** - Visual seat map with real-time availability
- **Ticket Booking** - Complete booking process with confirmation
- **Booking Management** - View and cancel existing bookings
- **Digital Ticket Generation** - Formatted ticket with all booking details

### 🔧 Administrative Features
- **Movie Management** - Add, edit, delete movies with comprehensive details
- **Showtime Management** - Create and manage movie showtimes across multiple halls
- **Dynamic Pricing** - Flexible pricing management for movies and individual showtimes
- **Customer Analytics** - View customer information and booking history
- **Revenue Reports** - Comprehensive financial and performance analytics
- **Booking Oversight** - Monitor all bookings across the system

## 🏗️ Technical Architecture

### Data Structures Used
- **Linked Lists** - Dynamic movie and showtime management
- **2D Arrays** - Seat arrangement and booking status
- **Structures** - Organized data representation for entities
- **Static Arrays** - Customer and booking storage

### Core Components
```
📁 CineBook System
├── 🎬 Movie Management (Linked List)
├── 🕐 Showtime Management (Linked List)
├── 🎫 Booking System (Array)
├── 👤 Customer Management (Array)
├── 💺 Seat Management (2D Array)
└── 📊 Analytics & Reporting
```

## 🚀 Getting Started

### Prerequisites
- C Compiler (GCC recommended)
- Terminal/Command Prompt
- Minimum 2MB RAM
- Any operating system (Windows/Linux/macOS)

### Installation & Setup

1. **Clone or Download** the source code
   ```bash
   # Save the code as cinebook.c
   ```

2. **Compile the Program**
   ```bash
   gcc -o cinebook cinebook.c
   ```

3. **Run the Application**
   ```bash
   ./cinebook          # Linux/macOS
   cinebook.exe        # Windows
   ```

## 📖 User Guide

### For Customers

1. **Launch Application** - Start the program and select "Customer Portal"
2. **Register/Login** - Create account with phone number or login to existing account
3. **Browse Movies** - View available movies with pricing and showtimes
4. **Book Tickets**:
   - Select desired movie
   - Choose showtime
   - Pick seats from visual seat map
   - Confirm booking and payment
5. **Manage Bookings** - View or cancel existing reservations

### For Administrators

1. **Access Admin Panel** - Use password: `admin123`
2. **Movie Management**:
   - Add new movies with details and base pricing
   - Edit existing movie information
   - Remove movies from system
3. **Showtime Management**:
   - Create showtimes for movies
   - Assign to different halls
   - Set individual showtime pricing
4. **Pricing Management**:
   - Update base movie prices
   - Modify individual showtime rates
   - Bulk price updates
5. **Analytics & Reports**:
   - View booking summaries
   - Generate revenue reports
   - Analyze movie performance
   - Customer management

## 🎯 System Specifications

### Capacity Limits
- **Movies**: Up to 10 concurrent movies
- **Showtimes**: 5 showtimes per movie
- **Seating**: 10 rows × 20 seats per hall (200 seats)
- **Customers**: Up to 50 registered customers
- **Bookings**: Maximum 100 concurrent bookings

### Default Configuration
- **Admin Password**: `admin123`
- **Seat Layout**: A-J rows, 1-20 columns
- **Currency**: Indian Rupees (₹)
- **Date Format**: YYYY-MM-DD
- **Time Format**: HH:MM AM/PM

## 📊 Sample Data

The system comes pre-loaded with demo data including:

### Movies
- **Avengers: Endgame** (Action/Sci-Fi) - 181 min - ₹250
- **The Shawshank Redemption** (Drama) - 142 min - ₹200  
- **Inception** (Sci-Fi/Action) - 148 min - ₹280
- **Parasite** (Thriller/Drama) - 132 min - ₹220

### Sample Customer
- **Name**: John Doe
- **Phone**: 9876543210
- **Email**: john@example.com

## 🔧 Code Structure

### Main Components

```c
// Core Data Structures
typedef struct Movie Movie;
typedef struct Showtime Showtime;
typedef struct Booking Booking;
typedef struct Customer Customer;

// Linked List Nodes
typedef struct MovieNode MovieNode;
typedef struct ShowtimeNode ShowtimeNode;

// Global Storage
MovieNode* movie_list;
ShowtimeNode* showtime_list;
Booking bookings[MAX_BOOKINGS];
Customer customers[MAX_CUSTOMERS];
```

### Key Functions
- `add_movie()` - Add new movie to linked list
- `add_showtime()` - Create new showtime
- `add_booking()` - Process ticket booking
- `display_seats()` - Show seat availability
- `generate_ticket()` - Create formatted ticket
- `manage_movie_pricing()` - Handle pricing updates

## 🎨 User Interface Features

- **Clear Screen Management** - Cross-platform screen clearing
- **Formatted Output** - Professional table layouts
- **Interactive Menus** - Intuitive navigation system
- **Visual Seat Maps** - ASCII-based seat selection
- **Ticket Generation** - Professional ticket formatting
- **Error Handling** - Comprehensive input validation

## 🔒 Security Features

- **Admin Authentication** - Password-protected admin access
- **Customer Authorization** - Phone-based customer identification
- **Booking Validation** - Prevents double booking and invalid selections
- **Data Integrity** - Consistent data state management

## 📈 Performance Optimizations

- **Efficient Searching** - Optimized ID-based lookups
- **Memory Management** - Dynamic allocation for scalability
- **Linked List Operations** - O(1) insertion, O(n) search
- **Minimal Memory Footprint** - Efficient data structure usage

## 🚀 Future Enhancements

- **File I/O Integration** - Persistent data storage
- **Advanced Pricing** - Time-based and demand-based pricing
- **Multiple Payment Methods** - Integration with payment gateways
- **Email Notifications** - Booking confirmations via email
- **Advanced Analytics** - Machine learning for demand prediction
- **Mobile App Interface** - GUI development
- **Multi-theater Support** - Chain management capabilities

## 🛠️ Troubleshooting

### Common Issues

1. **Compilation Errors**
   - Ensure all headers are included
   - Check for proper C compiler installation

2. **Memory Issues**
   - Verify sufficient system memory
   - Check for memory leaks in extended usage

3. **Input Problems**
   - Use proper input formats
   - Clear input buffer after scanf operations

4. **Display Issues**
   - Ensure terminal supports ANSI escape codes
   - Adjust terminal size for proper formatting

## 📄 License

This project is developed for educational purposes as part of a data structures course. Feel free to use and modify for learning and academic purposes.

## 🤝 Contributing

This project was developed as an academic exercise. For suggestions or improvements, please contact the development team.

## 📞 Support

For technical support or questions about the system, please reach out to the ShowTime Innovators development team.

---

**CineBook System v1.0** - Efficient Movie Ticket Booking Made Simple

*Developed with ❤️ by ShowTime Innovators*
