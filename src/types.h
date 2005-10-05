/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2003, 2004  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef REST_TYPES_H
#define REST_TYPES_H

typedef double integer_t;
typedef double real_t;
typedef int    bool_t;

/* -------------------------------------------------- */
/* double ended queue, very useful                    */
/* -------------------------------------------------- */

/**
 * \defgroup dqueue Double ended queue data type.
 * \ingroup internal
 */

typedef struct s_dqueue {
  real_t *begin;
  real_t *end;
  real_t *stor_begin;
  real_t *stor_end;
} dqueue_t;

int dqueue_init    (dqueue_t* q, long int size);
int dqueue_destroy (dqueue_t* q);
int dqueue_empty   (dqueue_t* q);
int dqueue_clear   (dqueue_t* q);
int dqueue_full    (dqueue_t* q);
long int dqueue_size    (dqueue_t* q);
real_t dqueue_pop     (dqueue_t* q);
real_t dqueue_pop_back(dqueue_t* q);
real_t dqueue_head    (dqueue_t* q);
real_t dqueue_back    (dqueue_t* q);
int dqueue_push    (dqueue_t* q, real_t elem);

/* -------------------------------------------------- */
/* Flexible vector                                    */
/* -------------------------------------------------- */

/** \defgroup vector Vector, dealing with arrays efficiently.
 * \ingroup types
 * 
 * The <code>vector_t</code> data type is a simple and efficient
 * interface to arrays containing real numbers. It is something
 * similar as (but much simpler than) the <code>vector</code> template
 * in the C++ standard library.
 *
 * Vectors are used extensively in \a igraph, all functions which
 * expects or returns a list of numbers use <code>vector_t</code> to
 * achive this.
 * 
 * The <code>vector_t</code> type susally uses <code>O(n)</code> space
 * to store <code>n</code> elements. Sometimes it uses more, this is
 * because vectors can shrink, but even if they shrink, the current
 * implementation does not free a single bit of memory.
 */

typedef struct s_vector {
  real_t* stor_begin;
  real_t* stor_end;
  real_t* end;
} vector_t;

/**
 * \ingroup vector
 * \brief Accessing an element of a vector
 * 
 * Usage: 
 * \verbatim VECTOR(v)[0] \endverbatim 
 * to access the first element of the vector, you can also use this in
 * assignments, like: 
 * \verbatim VECTOR(v)[10]=5; \endverbatim
 *
 * Note that there are no range checks right now.
 * This functionality might be redefined later as a real function
 * instead of a <code>#define</code>. 
 * @param v The vector object.
 * 
 * Time complexity: <code>O(1)</code>.
 */
#define VECTOR(v) ((v).stor_begin) /* DIRTY */
int vector_init      (vector_t* v, long int size);
int vector_init_copy (vector_t* v, real_t* data, long int length);
int vector_destroy   (vector_t* v);
int vector_reserve   (vector_t* v, long int size);
int vector_empty     (vector_t* v);
long int vector_size      (vector_t* v);
int vector_clear     (vector_t* v);
int vector_null      (vector_t* v);
int vector_push_back (vector_t* v, real_t e);
real_t vector_e         (vector_t* v, long int pos);
int vector_set       (vector_t* v, long int pos, real_t value);
int vector_add       (vector_t* v, long int pos, real_t value);
int vector_replace_first(vector_t* v, real_t old, real_t newe);
real_t vector_tail(vector_t *v);
real_t vector_pop_back(vector_t* v);
long int vector_find(vector_t* v, real_t elem);
int vector_change(vector_t* v, long int pos1, long int pos2);
int vector_order(vector_t* v, vector_t* res, integer_t maxval);
int vector_sort(vector_t *v);
int vector_resize(vector_t* v, long int newsize);
real_t vector_max(vector_t* v);
vector_t vector_as_vector(real_t *start, long int length);
int vector_copy_to(vector_t *v, real_t* to);
int vector_copy(vector_t *to, vector_t *from);
real_t vector_sum(vector_t *v);
real_t vector_prod(vector_t *v);
int vector_init_seq(vector_t *v, real_t from, real_t to);

/* -------------------------------------------------- */
/* Matrix, very similar to vector                     */
/* -------------------------------------------------- */

/** \defgroup matrix Matrix type, for storing real matrices efficienly. 
 * \ingroup types
 * 
 * This type is just an interface to vector.
 *
 * The <code>matrix_t</code> type ususally stores <code>n</code>
 * elements in <code>O(n)</code> space, but not always, see the
 * documentation of the vector type.
 */
typedef struct s_matrix {
  vector_t data;
  long int nrow, ncol;
} matrix_t;

/**
 * \ingroup matrix
 * \brief Accessing an element of a matrix.
 *
 * Note that there are no range checks right now. 
 * This functionality might be redefines as a proper function later. 
 * @param m The matrix object.
 * @param i The index of the row, starting with zero.
 * @param j The index of the column, starting with zero.
 *
 * Time complexity: <code>O(1)</code>.
 */
#define MATRIX(m,i,j) ((m).data.stor_begin[(m).nrow*(j)+(i)])
int matrix_init(matrix_t *m, long int nrow, long int ncol);
int matrix_destroy(matrix_t *m);
int matrix_resize(matrix_t *m, long int nrow, long int ncol);
long int matrix_size(matrix_t *m);
long int matrix_nrow(matrix_t *m);
long int matrix_ncol(matrix_t *m);
int matrix_copy_to(matrix_t *m, real_t *to);
int matrix_null(matrix_t *m);

/* -------------------------------------------------- */
/* Plain stack                                        */
/* -------------------------------------------------- */

/**
 * \defgroup stack Stack data type.
 * \ingroup internal
 */

typedef struct s_stack {
  real_t* stor_begin;
  real_t* stor_end;
  real_t* end;
} igraph_stack_t;

int igraph_stack_init       (igraph_stack_t* s, long int size);
int igraph_stack_destroy    (igraph_stack_t* s);
int igraph_stack_reserve    (igraph_stack_t* s, long int size);
int igraph_stack_empty      (igraph_stack_t* s);
long int igraph_stack_size       (igraph_stack_t* s);
int igraph_stack_clear      (igraph_stack_t* s);
int igraph_stack_push       (igraph_stack_t* s, real_t elem);
real_t igraph_stack_pop        (igraph_stack_t* s);

/* -------------------------------------------------- */
/* Multi set                                          */
/* -------------------------------------------------- */

/**
 * \defgroup multiset Multiset data type.
 * \ingroup internal
 */

typedef struct s_multiset {
  real_t* stor_begin;
  real_t* stor_end;
  real_t*end;
} multiset_t;

int multiset_init    (multiset_t* m, long int size);
int multiset_destroy (multiset_t* m);
int multiset_reserve (multiset_t* m, long int size);
int multiset_add     (multiset_t* m, real_t elem);
int multiset_clear   (multiset_t* m);
real_t multiset_choose  (multiset_t* m);
real_t multiset_choose_random(multiset_t* m);
real_t multiset_choose_remove (multiset_t* m);
real_t multiset_choose_remove_random(multiset_t* m);
long int multiset_size(multiset_t* m);
int multiset_remove (multiset_t* m, real_t elem);
int multiset_remove_all (multiset_t* m, real_t elem);
real_t* multiset_get_vector(multiset_t * m);
long int multiset_count(multiset_t* m, real_t elem);
long int multiset_count_different(multiset_t* m, real_t elem);
real_t multiset_choose_random_different(multiset_t* m, real_t elem);

/* -------------------------------------------------- */
/* Heap                                               */
/* -------------------------------------------------- */

/**
 * \defgroup heap Heap data type.
 * \ingroup internal
 */

typedef struct s_heap {
  real_t* stor_begin;
  real_t* stor_end;
  real_t* end;
  int destroy;
} heap_t;

int heap_init           (heap_t* h, long int size);
int heap_init_array     (heap_t *t, real_t* data, long int len);
int heap_destroy        (heap_t* h);
int heap_empty          (heap_t* h);
int heap_push           (heap_t* h, real_t elem);
real_t heap_max       (heap_t* h);
real_t heap_delete_max(heap_t* h);
long int heap_size      (heap_t* h);
int heap_reserve        (heap_t* h, long int size);

int heap_i_build(real_t* arr, long int size, long int head);
int heap_i_shift_up(real_t* arr, long int size, long int elem);
int heap_i_sink(real_t* arr, long int size, long int head);
int heap_i_switch(real_t* arr, long int e1, long int e2);

/* -------------------------------------------------- */
/* Indexed heap                                       */
/* -------------------------------------------------- */

/**
 * \defgroup indheap Indexed heap data type.
 * \ingroup internal
 */

typedef struct s_indheap {
  real_t* stor_begin;
  real_t* stor_end;
  real_t* end;
  int destroy;
  long int* index_begin;
} indheap_t;

int indheap_init           (indheap_t* h, long int size);
int indheap_init_array     (indheap_t *t, real_t* data, long int len);
int indheap_destroy        (indheap_t* h);
int indheap_empty          (indheap_t* h);
int indheap_push           (indheap_t* h, real_t elem);
real_t indheap_max       (indheap_t* h);
real_t indheap_delete_max(indheap_t* h);
long int indheap_size      (indheap_t* h);
int indheap_reserve        (indheap_t* h, long int size);
long int indheap_max_index(indheap_t *h);

int indheap_i_build(indheap_t* h, long int head);
int indheap_i_shift_up(indheap_t* h, long int elem);
int indheap_i_sink(indheap_t* h, long int head);
int indheap_i_switch(indheap_t* h, long int e1, long int e2);

/* -------------------------------------------------- */
/* Doubly indexed heap                                */
/* -------------------------------------------------- */

/* This is a heap containing double elements and 
   two indices, its intended usage is the storage of
   weighted edges.
*/

/**
 * \defgroup doubleindheap Doubly indexed heap data type.
 * \ingroup internal
 */

typedef struct s_indheap_d {
  real_t* stor_begin;
  real_t* stor_end;
  real_t* end;
  int destroy;
  long int* index_begin;
  long int* index2_begin;
} d_indheap_t;

int d_indheap_init           (d_indheap_t* h, long int size);
int d_indheap_destroy        (d_indheap_t* h);
int d_indheap_empty          (d_indheap_t* h);
int d_indheap_push           (d_indheap_t* h, real_t elem, 
			      long int idx, long int idx2);
real_t d_indheap_max       (d_indheap_t* h);
real_t d_indheap_delete_max(d_indheap_t* h);
long int d_indheap_size      (d_indheap_t* h);
int d_indheap_reserve        (d_indheap_t* h, long int size);
int d_indheap_max_index(d_indheap_t *h, long int *idx, long int *idx2);

int d_indheap_i_build(d_indheap_t* h, long int head);
int d_indheap_i_shift_up(d_indheap_t* h, long int elem);
int d_indheap_i_sink(d_indheap_t* h, long int head);
int d_indheap_i_switch(d_indheap_t* h, long int e1, long int e2);

#endif
