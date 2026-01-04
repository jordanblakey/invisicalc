/* invisicalc-window.c
 *
 * Copyright 2026 invisible
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gdk/gdkkeysyms.h>

#include "invisicalc-window.h"

struct _InvisicalcWindow {
  AdwApplicationWindow parent_instance;

  /* Template widgets */
  GtkEntry *display;
  GtkGrid *keypad;
};

static void on_equal_clicked(GtkButton *btn, InvisicalcWindow *self);
static void on_back_clicked(GtkButton *btn, InvisicalcWindow *self);

static void on_input_clicked(GtkButton *btn, InvisicalcWindow *self) {
  const char *label = gtk_button_get_label(btn);
  GtkEditable *editable = GTK_EDITABLE(self->display);
  int pos = -1;

  gtk_editable_insert_text(editable, label, -1, &pos);
  gtk_editable_set_position(editable, -1);
}

static void on_clear_clicked(GtkButton *btn, InvisicalcWindow *self) {
  gtk_editable_set_text(GTK_EDITABLE(self->display), "");
}

static void on_back_clicked(GtkButton *btn, InvisicalcWindow *self) {
  GtkEditable *editable = GTK_EDITABLE(self->display);
  const char *text = gtk_editable_get_text(editable);
  int len = g_utf8_strlen(text, -1);

  if (len > 0)
    gtk_editable_delete_text(editable, len - 1, len);
}

static const char *get_button_name_for_key(guint keyval) {
  switch (keyval) {
  case GDK_KEY_KP_1:
  case GDK_KEY_1:
  case GDK_KEY_KP_End:
    return "one";
  case GDK_KEY_KP_2:
  case GDK_KEY_2:
  case GDK_KEY_KP_Down:
    return "two";
  case GDK_KEY_KP_3:
  case GDK_KEY_3:
  case GDK_KEY_KP_Page_Down:
    return "three";
  case GDK_KEY_KP_4:
  case GDK_KEY_4:
  case GDK_KEY_KP_Left:
    return "four";
  case GDK_KEY_KP_5:
  case GDK_KEY_5:
  case GDK_KEY_KP_Begin:
    return "five";
  case GDK_KEY_KP_6:
  case GDK_KEY_6:
  case GDK_KEY_KP_Right:
    return "six";
  case GDK_KEY_KP_7:
  case GDK_KEY_7:
  case GDK_KEY_KP_Home:
    return "seven";
  case GDK_KEY_KP_8:
  case GDK_KEY_8:
  case GDK_KEY_KP_Up:
    return "eight";
  case GDK_KEY_KP_9:
  case GDK_KEY_9:
  case GDK_KEY_KP_Page_Up:
    return "nine";
  case GDK_KEY_KP_0:
  case GDK_KEY_0:
  case GDK_KEY_KP_Insert:
    return "zero";
  case GDK_KEY_KP_Add:
  case GDK_KEY_plus:
    return "add";
  case GDK_KEY_KP_Subtract:
  case GDK_KEY_minus:
    return "subtract";
  case GDK_KEY_KP_Multiply:
  case GDK_KEY_multiply:
  case GDK_KEY_asterisk:
    return "multiply";
  case GDK_KEY_KP_Divide:
  case GDK_KEY_division:
  case GDK_KEY_slash:
    return "divide";
  case GDK_KEY_KP_Decimal:
  case GDK_KEY_decimalpoint:
  case GDK_KEY_period:
  case GDK_KEY_KP_Delete:
    return "decimal";
  case GDK_KEY_KP_Enter:
  case GDK_KEY_KP_Equal:
  case GDK_KEY_Return:
  case GDK_KEY_equal:
    return "equals";
  case GDK_KEY_BackSpace:
    return "back";
  case GDK_KEY_C:
  case GDK_KEY_c:
  case GDK_KEY_Num_Lock:
    return "clear";
  case GDK_KEY_asciicircum:
    return "exponent";
  case GDK_KEY_parenleft:
    return "left_parenthesis";
  case GDK_KEY_parenright:
    return "right_parenthesis";
  default:
    return NULL;
  }
}

static char get_char_for_key(guint keyval) {
  switch (keyval) {
  case GDK_KEY_KP_1:
  case GDK_KEY_1:
  case GDK_KEY_KP_End:
    return '1';
  case GDK_KEY_KP_2:
  case GDK_KEY_2:
  case GDK_KEY_KP_Down:
    return '2';
  case GDK_KEY_KP_3:
  case GDK_KEY_3:
  case GDK_KEY_KP_Page_Down:
    return '3';
  case GDK_KEY_KP_4:
  case GDK_KEY_4:
  case GDK_KEY_KP_Left:
    return '4';
  case GDK_KEY_KP_5:
  case GDK_KEY_5:
  case GDK_KEY_KP_Begin:
    return '5';
  case GDK_KEY_KP_6:
  case GDK_KEY_6:
  case GDK_KEY_KP_Right:
    return '6';
  case GDK_KEY_KP_7:
  case GDK_KEY_7:
  case GDK_KEY_KP_Home:
    return '7';
  case GDK_KEY_KP_8:
  case GDK_KEY_8:
  case GDK_KEY_KP_Up:
    return '8';
  case GDK_KEY_KP_9:
  case GDK_KEY_9:
  case GDK_KEY_KP_Page_Up:
    return '9';
  case GDK_KEY_KP_0:
  case GDK_KEY_0:
  case GDK_KEY_KP_Insert:
    return '0';
  case GDK_KEY_KP_Add:
  case GDK_KEY_plus:
    return '+';
  case GDK_KEY_KP_Subtract:
  case GDK_KEY_minus:
    return '-';
  case GDK_KEY_KP_Multiply:
  case GDK_KEY_multiply:
  case GDK_KEY_asterisk:
    return '*';
  case GDK_KEY_KP_Divide:
  case GDK_KEY_division:
  case GDK_KEY_slash:
    return '/';
  case GDK_KEY_KP_Decimal:
  case GDK_KEY_decimalpoint:
  case GDK_KEY_period:
  case GDK_KEY_KP_Delete:
    return '.';
  case GDK_KEY_asciicircum:
    return '^';
  case GDK_KEY_parenleft:
    return '(';
  case GDK_KEY_parenright:
    return ')';
  default:
    return 0;
  }
}

static GtkWidget *get_button_by_name(InvisicalcWindow *self,
                                     const char *button_name) {
  GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(self->keypad));
  while (child) {
    if (GTK_IS_BUTTON(child)) {
      const char *name = gtk_widget_get_name(child);
      if (g_strcmp0(name, button_name) == 0) {
        return child;
      }
    }
    child = gtk_widget_get_next_sibling(child);
  }
  return NULL;
}

static void set_button_active(InvisicalcWindow *self, const char *button_name,
                              gboolean active) {
  GtkWidget *child = get_button_by_name(self, button_name);
  if (child) {
    if (active)
      gtk_widget_add_css_class(child, "active-key");
    else
      gtk_widget_remove_css_class(child, "active-key");
  }
}

static void on_key_released(GtkEventControllerKey *controller, guint keyval,
                            guint keycode, GdkModifierType state,
                            gpointer user_data) {
  InvisicalcWindow *self = INVISICALC_WINDOW(user_data);
  const char *btn_name = get_button_name_for_key(keyval);
  if (btn_name) {
    set_button_active(self, btn_name, FALSE);
  }
}

static void on_paste_received(GObject *source_object, GAsyncResult *res,
                              gpointer user_data) {
  GdkClipboard *clipboard = GDK_CLIPBOARD(source_object);
  InvisicalcWindow *self = INVISICALC_WINDOW(user_data);
  char *text;
  GError *error = NULL;

  text = gdk_clipboard_read_text_finish(clipboard, res, &error);
  if (text) {
    GtkEditable *editable = GTK_EDITABLE(self->display);
    int pos;

    /* Append to end */
    gtk_editable_set_position(editable, -1);
    pos = gtk_editable_get_position(editable);
    gtk_editable_insert_text(editable, text, -1, &pos);
    gtk_editable_set_position(editable, -1);
    g_free(text);
  } else {
    if (error) {
      g_warning("Failed to paste: %s", error->message);
      g_error_free(error);
    }
  }
}

static gboolean on_key_pressed(GtkEventControllerKey *controller, guint keyval,
                               guint keycode, GdkModifierType state,
                               gpointer user_data) {
  InvisicalcWindow *self = INVISICALC_WINDOW(user_data);
  const char *btn_name = get_button_name_for_key(keyval);
  char value = get_char_for_key(keyval);

  // Check for specific keys using GDK_KEY constants
  if (keyval == GDK_KEY_Escape) {
    g_print("Escape key pressed! Closing...\n");
    return TRUE; // Stop event propagation
  }

  // Handle Ctrl+C to Select All + Copy
  if ((state & GDK_CONTROL_MASK) &&
      (keyval == GDK_KEY_c || keyval == GDK_KEY_C)) {
    GdkClipboard *clipboard =
        gtk_widget_get_clipboard(GTK_WIDGET(self->display));
    const char *text = gtk_editable_get_text(GTK_EDITABLE(self->display));

    gdk_clipboard_set_text(clipboard, text);
    gtk_editable_select_region(GTK_EDITABLE(self->display), 0, -1);

    return TRUE;
  }

  /* Handle Ctrl+V to Paste at end */
  if ((state & GDK_CONTROL_MASK) &&
      (keyval == GDK_KEY_v || keyval == GDK_KEY_V)) {
    GdkClipboard *clipboard =
        gtk_widget_get_clipboard(GTK_WIDGET(self->display));
    gdk_clipboard_read_text_async(clipboard, NULL, on_paste_received, self);
    return TRUE;
  }

  if (btn_name) {
    GtkWidget *btn = get_button_by_name(self, btn_name);
    if (btn) {
      if (gtk_widget_has_css_class(btn, "active-key")) {
        return TRUE; // Ignore key repeat
      }
      gtk_widget_add_css_class(btn, "active-key");
    }
  }

  // If the entry has focus, let it handle the input natively,
  // BUT we still want to intercept the Enter/Equal keys for evaluation.
  if (gtk_widget_has_focus(GTK_WIDGET(self->display))) {
    if (g_strcmp0(btn_name, "equals") == 0) {
      on_equal_clicked(NULL, self);
      return TRUE;
    }
    return FALSE;
  }

  // Logic handling
  if (g_strcmp0(btn_name, "equals") == 0) {
    on_equal_clicked(NULL, self);
    return TRUE;
  } else if (g_strcmp0(btn_name, "back") == 0) {
    on_back_clicked(NULL, self);
    return TRUE;
  } else if (g_strcmp0(btn_name, "clear") == 0) {
    on_clear_clicked(NULL, self);
    return TRUE;
  } else if (value != 0) {
    // Number/Operator input
    GtkEditable *editable = GTK_EDITABLE(self->display);
    int pos = -1;
    char text[2] = {value, '\0'}; // Create a null-terminated string
    gtk_editable_insert_text(editable, text, -1, &pos);
    gtk_editable_set_position(editable, -1);
    return TRUE;
  }

  // Example: Detect Ctrl + S
  if ((state & GDK_CONTROL_MASK) && keyval == GDK_KEY_s) {
    g_print("Save shortcut (Ctrl+S) detected.\n");
    return TRUE;
  }

  g_print("Key pressed: %s (code: %u)\n", gdk_keyval_name(keyval), keycode);
  return FALSE; // Let the event propagate to other widgets
}

#include <math.h>

typedef enum {
  TOKEN_NUMBER,
  TOKEN_OPERATOR,
  TOKEN_LPAREN,
  TOKEN_RPAREN
} TokenType;

typedef struct {
  TokenType type;
  double number;
  char op;
} Token;

static void free_token(gpointer data) { g_free(data); }

static int get_precedence(char op) {
  switch (op) {
  case '^':
    return 3;
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 1;
  default:
    return 0;
  }
}

static int is_right_associative(char op) { return op == '^'; }

static double evaluate_expression(const char *expression) {
  GList *tokens = NULL; /* Initial token list */
  GQueue *output_queue = g_queue_new();
  GQueue *op_stack = g_queue_new();
  GList *l;
  char number_buf[64];
  int n_idx = 0;
  int i;
  TokenType last_type =
      TOKEN_OPERATOR; /* Start implies expecting a number or unary */
  double result = 0;
  GQueue *eval_stack;

  /* 1. Tokenize */
  for (i = 0; expression[i] != '\0'; i++) {
    char c = expression[i];

    if ((c >= '0' && c <= '9') || c == '.') {
      if (n_idx == 0 && last_type == TOKEN_RPAREN) {
        Token *t = g_new0(Token, 1);
        t->type = TOKEN_OPERATOR;
        t->op = '*';
        tokens = g_list_append(tokens, t);
      }

      if (n_idx < sizeof(number_buf) - 1)
        number_buf[n_idx++] = c;
    } else {
      /* Flush number if present */
      if (n_idx > 0) {
        Token *t = g_new0(Token, 1);
        t->type = TOKEN_NUMBER;
        number_buf[n_idx] = '\0';
        t->number = g_ascii_strtod(number_buf, NULL);
        tokens = g_list_append(tokens, t);
        n_idx = 0;
        last_type = TOKEN_NUMBER;
      }

      if (c == '(') {
        Token *t;

        if (last_type == TOKEN_NUMBER || last_type == TOKEN_RPAREN) {
          Token *mult = g_new0(Token, 1);
          mult->type = TOKEN_OPERATOR;
          mult->op = '*';
          tokens = g_list_append(tokens, mult);
        }

        t = g_new0(Token, 1);
        t->type = TOKEN_LPAREN;
        t->op = '(';
        tokens = g_list_append(tokens, t);
        last_type = TOKEN_LPAREN;
      } else if (c == ')') {
        Token *t = g_new0(Token, 1);
        t->type = TOKEN_RPAREN;
        t->op = ')';
        tokens = g_list_append(tokens, t);
        last_type = TOKEN_RPAREN;
      } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        char op = c;

        /* Check for ** (exponentiation) */
        if (c == '*' && expression[i + 1] == '*') {
          op = '^';
          i++; /* Skip the second * */
        }

        /* Check for unary minus:
         * Unary minus is valid at start or after operator or after '(' */
        if (op == '-' &&
            (last_type == TOKEN_OPERATOR || last_type == TOKEN_LPAREN)) {
          if (n_idx < sizeof(number_buf) - 1)
            number_buf[n_idx++] = op;
          /* n_idx is growing, next loop will continue adding digits */
        } else {
          Token *t = g_new0(Token, 1);
          t->type = TOKEN_OPERATOR;
          t->op = op;
          tokens = g_list_append(tokens, t);
          last_type = TOKEN_OPERATOR;
        }
      }
    }
  }
  /* Flush final number */
  if (n_idx > 0) {
    Token *t = g_new0(Token, 1);
    t->type = TOKEN_NUMBER;
    number_buf[n_idx] = '\0';
    t->number = g_ascii_strtod(number_buf, NULL);
    tokens = g_list_append(tokens, t);
  }

  /* 2. Shunting Yard (Infix to RPN) */
  for (l = tokens; l != NULL; l = l->next) {
    Token *t = (Token *)l->data;
    if (t->type == TOKEN_NUMBER) {
      g_queue_push_tail(output_queue, t);
    } else if (t->type == TOKEN_OPERATOR) {
      while (!g_queue_is_empty(op_stack)) {
        Token *top = (Token *)g_queue_peek_head(op_stack);
        int prec_cur, prec_top;

        if (top->type == TOKEN_LPAREN)
          break;

        prec_cur = get_precedence(t->op);
        prec_top = get_precedence(top->op);

        if (prec_top > prec_cur ||
            (prec_top == prec_cur && !is_right_associative(t->op))) {
          g_queue_push_tail(output_queue, g_queue_pop_head(op_stack));
        } else {
          break;
        }
      }
      g_queue_push_head(op_stack, t);
    } else if (t->type == TOKEN_LPAREN) {
      g_queue_push_head(op_stack, t);
    } else if (t->type == TOKEN_RPAREN) {
      while (!g_queue_is_empty(op_stack)) {
        Token *top = (Token *)g_queue_peek_head(op_stack);
        if (top->type == TOKEN_LPAREN) {
          g_queue_pop_head(op_stack); /* Pop '(' */
          break;
        }
        g_queue_push_tail(output_queue, g_queue_pop_head(op_stack));
      }
    }
  }
  /* Pop remaining */
  while (!g_queue_is_empty(op_stack)) {
    Token *t = (Token *)g_queue_pop_head(op_stack);
    if (t->type !=
        TOKEN_LPAREN) /* Should not happen if balanced, but safe check */
      g_queue_push_tail(output_queue, t);
  }
  g_queue_free(op_stack); /* Stack structure free, content was moved */

  /* 3. Evaluate RPN */
  eval_stack = g_queue_new();
  while (!g_queue_is_empty(output_queue)) {
    Token *t = (Token *)g_queue_pop_head(output_queue);
    if (t->type == TOKEN_NUMBER) {
      double *val = g_new(double, 1);
      *val = t->number;
      g_queue_push_head(eval_stack, val);
    } else if (t->type == TOKEN_OPERATOR) {
      double *v2 = (double *)g_queue_pop_head(eval_stack);
      double *v1 = (double *)g_queue_pop_head(eval_stack);

      if (v1 && v2) {
        double res = 0;
        switch (t->op) {
        case '+':
          res = *v1 + *v2;
          break;
        case '-':
          res = *v1 - *v2;
          break;
        case '*':
          res = *v1 * *v2;
          break;
        case '/':
          if (*v2 != 0)
            res = *v1 / *v2;
          break;
        case '^':
          res = pow(*v1, *v2);
          break;
        default:
          break;
        }
        *v1 = res; /* Reuse v1 memory */
        g_queue_push_head(eval_stack, v1);
        g_free(v2);
      } else {
        /* Error case: not enough operands */
        if (v2)
          g_free(v2);
        if (v1)
          g_free(v1);
      }
    }
  }

  if (!g_queue_is_empty(eval_stack)) {
    double *final_val = (double *)g_queue_pop_head(eval_stack);
    result = *final_val;
    g_free(final_val);
  }

  /* Cleanup */
  g_queue_free_full(eval_stack, g_free);
  g_queue_free(output_queue);
  g_list_free_full(tokens, free_token);

  return result;
}

static void on_equal_clicked(GtkButton *btn, InvisicalcWindow *self) {
  /* Simplified logic: Get text, replace non-ascii operators, evaluate */
  const char *text = gtk_editable_get_text(GTK_EDITABLE(self->display));
  GString *expr = g_string_new(text);
  double result;
  char *res_str;

  /* Normalize operators to standard C types */
  /* Remove the ^ -> ** replacement since parser supports ^ directly */
  g_string_replace(expr, "×", "*", 0);
  g_string_replace(expr, "÷", "/", 0);
  g_string_replace(expr, "−", "-", 0); /* Minus sign vs hyphen */

  result = evaluate_expression(expr->str);
  res_str = g_strdup_printf("%.10g", result);

  gtk_editable_set_text(GTK_EDITABLE(self->display), res_str);

  g_free(res_str);
  g_string_free(expr, TRUE);
  gtk_editable_set_position(GTK_EDITABLE(self->display), -1);
}

G_DEFINE_FINAL_TYPE(InvisicalcWindow, invisicalc_window,
                    ADW_TYPE_APPLICATION_WINDOW)

static void invisicalc_window_class_init(InvisicalcWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

  gtk_widget_class_set_template_from_resource(widget_class,
                                              "/org/gnome/invisicalc/main.ui");
  gtk_widget_class_bind_template_child(widget_class, InvisicalcWindow, display);
  gtk_widget_class_bind_template_child(widget_class, InvisicalcWindow, keypad);

  gtk_widget_class_bind_template_callback(widget_class, on_input_clicked);
  gtk_widget_class_bind_template_callback(widget_class, on_clear_clicked);
  gtk_widget_class_bind_template_callback(widget_class, on_back_clicked);
  gtk_widget_class_bind_template_callback(widget_class, on_equal_clicked);
  gtk_widget_class_bind_template_callback(widget_class, on_key_pressed);
  gtk_widget_class_bind_template_callback(widget_class, on_key_released);
}

static void invisicalc_window_init(InvisicalcWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}
