/* 
 * File:   Table.h
 * Author: jungj5
 *
 * Created on February 16, 2014, 2:01 AM
 */

#ifndef TABLE_H
#define	TABLE_H

//Typedefs
typedef unsigned int size_type;


template <class T> 



class Table {
public:
    
    
    
    //Constructors, Assignment Operator, Destructor
    Table() {this->create();}
    Table(size_type rows, size_type cols, T character ) {this ->create(rows, cols, character);}
    Table(const Table& t) {copy(t);}
    const Table& operator= (const Table& t);
    ~Table() { deleteValues(); }
    
    //Modifiers
    void push_back_row(const std::vector<T> row2);
    void push_back_column(const std::vector<T> row3);
    void pop_back_row();
    void pop_back_column();
    void set(int row, int col, T new_value);
    void deleteValues(); 
    
    
    //Accessors
    int numRows() {return rows;}
    int numColumns() {return cols;}
    void print();
    T get(int rownum, int colnum); 
    
    
    //Bonus Functions
    void push_back_rows(Table<T>& t);
    void push_back_columns(Table<T>& t);
            
    
private: 
    //Private Member Functions
    void create();
    void create(size_type rows1, size_type cols1, T character );
    void copy(const Table<T>& t);
    
    
    unsigned int rows;
    unsigned int cols;
    T ** values;
    
            
};

template <class T>
void Table<T>::create() {
    rows = 0;
    cols = 0;
    values = new T*[rows];
}

template <class T> 
void Table<T>::create(size_type rows1, size_type cols1, T character) {
    rows = rows1;
    cols = cols1;
    values = new T *[rows];
    for (int i = 0; i < rows; ++i ) {
        values[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            values[i][j] = character;
       
        }
        

    }
}

template <class T>
T Table<T>::get(int rownum, int colnum) {
       if (rownum < 0 || rownum >= rows || colnum < 0 || colnum >= cols ) {
       std::cerr << "Invalid bounds for set function";
       exit(1);
    }
       return values[rownum][colnum];
}

template <class T>
void Table<T>::print() {
    //table: 2 rows, 5 cols
    std::cout << "table: " << rows << " rows, " << cols << " cols" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << values[i][j];
            if (j < cols) {
                std::cout << " ";
        }
    }
        if (i < rows) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}





template <class T>
void Table<T>::set(int row, int col, T new_value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols ) {
        std::cerr << "Invalid bounds for set function";
        exit(1);
    }
    values[row][col] = new_value;
}

template <class T> void Table<T>::push_back_row(const std::vector<T> row2) {
    if ( row2.size() != cols) {
        std::cerr << "Invalid number of row values in vector to push back";
        exit(1);
    }
    
    
    T** new_values = new T *[rows+ 1];
    for (int i = 0; i < rows ; ++i) {
        
        new_values[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            new_values[i][j] = values[i][j];
        }
    
    }
    
    new_values[rows] = new T[cols];
    for (int k = 0; k < row2.size(); ++k) {

        new_values[rows][k] = row2[k];
        
    }
    deleteValues();
    rows += 1;
    values = new_values;
    

}


template <class T>
void Table<T>::pop_back_column() {
    if (cols == 0) {
        std::cerr << "Error: Can't pop back column of 0 cols";
        exit(1);
    }
    cols = cols - 1;
    T** new_values = new T *[rows];
    for (int i = 0; i < rows; ++i) {
        new_values[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            new_values[i][j] = values[i][j];
        }
    }
    deleteValues();
    values = new_values;
}

template <class T>
void Table<T>::push_back_column(const std::vector<T> row3) {
    if ( row3.size() != rows) {
        std::cerr<< "Invalid number of column values in vector to push back";
        exit(1);
    }
    cols = cols + 1;
    T** new_values2 = new T *[rows];
    for (int i = 0; i < rows; ++i) {
        new_values2[i] = new T[cols];
        for (int j = 0; j < cols-1; ++j) {
            new_values2[i][j] = values[i][j];
        }
        new_values2[i][cols-1] = row3[i];
    }
    deleteValues();
    values = new_values2;
}


template <class T> 
void Table<T>::pop_back_row() {
    if (rows == 0) {
        std::cerr << "Error: Can't pop back rows of 0 rows";
        exit(1);
    }
    rows = rows - 1;
    T ** new_values3 = new T *[rows];
    for (int i = 0; i < rows; ++i) {
        new_values3[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            new_values3[i][j] = values[i][j];
        }
        
    }
    //deleteValues();
    for (int i = 0; i < rows + 1 ; ++i ) {
        delete [] values[i];
        
    }
    delete [] values;
    values = new_values3;
}
template <class T>
void Table<T>::copy(const Table<T>& t) {
    this->cols = t.cols;
    this->rows = t.rows;
    this->values = new T*[this->rows];
    
    //Copy the data yo
    for (int i = 0; i < t.rows; ++i ) {
        values[i] = new T[t.cols];
        for (int j = 0; j < t.cols; ++j) {
            values[i][j] = t.values[i][j];
       
        }
        

    }
}

template <class T>
const Table<T>& Table<T>::operator= (const Table& t) {  //const Table& operator= (const Table& t);
    if (this != &t) {
        deleteValues();
        this -> copy(t);
    }
    return *this;
}

template <class T>
void Table<T>::deleteValues() {
    //std::cout<<"jfkdjd" << std::endl;
    for (int i = 0; i < rows; ++i ) {
        delete [] values[i];
        
    }
    delete [] values;
}

template <class T>
void Table<T>::push_back_rows(Table<T>& t) {
    if ( t.cols != cols) {
        std::cerr << "Invalid # of cols for push_back_rows";
        exit(1);
    }
    
    
    T** new_values = new T *[rows+ t.rows];
    for (int i = 0; i < rows ; ++i) {
        
        new_values[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            new_values[i][j] = values[i][j];
        }
    
    }
    int count = 0;
    for (int L = rows; L < rows + t.rows; ++L ) {
        new_values[L] = new T[cols];
        for (int M = 0; M < cols; ++M) {
            new_values[L][M] = t.values[count][M];
        }
        count += 1;
    
    }
    

    
    rows = rows + t.rows;
    for (int i = 0; i < rows - t.rows ; ++i ) {
        delete [] values[i];
        
    }
    delete [] values;
    values = new_values;
    

    
    
}

template <class T>
void Table<T>::push_back_columns(Table<T>& t) {
    if (rows != t.rows) {
        std::cerr<< "Invalid number of rows to use push_back_columns";
        exit(1);
    }
    cols = cols + t.cols;
    T** new_values2 = new T *[rows];
    
    for (int i = 0; i < rows; ++i) {
        int count1 = 0;
        new_values2[i] = new T[cols];
        for (int j = 0; j < cols - t.cols; ++j) {
            new_values2[i][j] = values[i][j];
        }
        for (int k = cols - t.cols; k < cols; ++k) {
        std::cout << t.values[i][count1] << std::endl;
        
        new_values2[i][k] = t.values[i][count1];
        count1 += 1;
        
        
    
        }
        
    }
    deleteValues();
    values = new_values2;
    
}
 


#endif	/* TABLE_H */

