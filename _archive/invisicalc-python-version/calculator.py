import sys
import os
import gi

gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, Gdk, Gio

BUTTON_SPACING = 2
DEFAULT_WINDOW_SIZE = (520, 400)

class CalculatorWindow(Gtk.ApplicationWindow):
    def __init__(self, app):
        super().__init__(application=app)
        self.set_title("invisicalc")
        self.set_default_size(*DEFAULT_WINDOW_SIZE)
        self.set_resizable(True)

        # Set up icon
        display = self.get_display()
        icon_theme = Gtk.IconTheme.get_for_display(display)
        
        # Add local path for development, but system paths are checked by default
        base_path = os.path.dirname(os.path.realpath(__file__))
        if os.path.exists(os.path.join(base_path, "invisicalc_icon.svg")):
            icon_theme.add_search_path(base_path)
        
        self.set_icon_name("invisicalc_icon")

        # Main vertical box
        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        self.set_child(main_box)

        # Key Controller
        key_controller = Gtk.EventControllerKey()
        key_controller.connect("key-pressed", self.on_key_pressed)
        self.add_controller(key_controller)

        # Load CSS
        self.load_css()

        # Display (Entry)
        self.display = Gtk.Entry()
        self.display.set_alignment(1.0) # Right aligned
        self.display.set_can_focus(False) # Don't allow typing directly for now
        self.display.add_css_class("display")
        main_box.append(self.display)

        # Grid for buttons
        grid = Gtk.Grid()
        grid.add_css_class("grid")
        grid.set_column_spacing(BUTTON_SPACING)
        grid.set_row_spacing(BUTTON_SPACING)
        grid.set_row_homogeneous(True)
        grid.set_column_homogeneous(True)
        # grid.set_halign(Gtk.Align.CENTER) # Center grid horizontally
        main_box.append(grid)

        # Button Layout
        self.create_buttons(grid)
        
        self.current_expression = ""

    def create_buttons(self, grid):
        # Label, Col, Row, Width, Height, Class
        layout = [
            ('C', 0, 0, 1, 1, 'special'), ('←', 1, 0, 1, 1, 'special'), ('÷', 2, 0, 1, 1, 'operator'), ('×', 3, 0, 1, 1, 'operator'),
            ('7', 0, 1, 1, 1, 'number'),  ('8', 1, 1, 1, 1, 'number'),   ('9', 2, 1, 1, 1, 'number'),   ('-', 3, 1, 1, 1, 'operator'),
            ('4', 0, 2, 1, 1, 'number'),  ('5', 1, 2, 1, 1, 'number'),   ('6', 2, 2, 1, 1, 'number'),   ('+', 3, 2, 1, 1, 'operator'),
            ('1', 0, 3, 1, 1, 'number'),  ('2', 1, 3, 1, 1, 'number'),   ('3', 2, 3, 1, 1, 'number'),   ('=', 3, 3, 1, 2, 'operator'),
            ('0', 0, 4, 2, 1, 'number'),  ('.', 2, 4, 1, 1, 'number'),
        ]

        for label, col, row, width, height, cls in layout:
            button = Gtk.Button(label=label)
            if cls:
                button.add_css_class(cls)
            button.set_hexpand(True)
            button.set_vexpand(True)
            button.set_can_focus(False) # Disable focus so key events go to the window controller
            grid.attach(button, col, row, width, height)
            button.connect("clicked", self.on_button_clicked, label)

    def load_css(self):
        css_provider = Gtk.CssProvider()
        try:
            base_path = os.path.dirname(os.path.realpath(__file__))
            css_path = os.path.join(base_path, 'style.css')
            
            css_provider.load_from_path(css_path)
            Gtk.StyleContext.add_provider_for_display(
                Gdk.Display.get_default(),
                css_provider,
                Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
            )
        except Exception as e:
            print(f"Failed to load CSS: {e}")

    def on_button_clicked(self, button, label):
        if label == 'C':
            self.current_expression = ""
        elif label == '←':
            self.current_expression = self.current_expression[:-1]
        elif label == '=':
            try:
                self.current_expression = self.current_expression.replace('×', '*')
                self.current_expression = self.current_expression.replace('÷', '/')
                # Basic safety replace to avoid evil
                intermediate_result = eval(self.current_expression)
                if float(intermediate_result) % 1 == 0:
                    intermediate_result = int(intermediate_result)
                result = str(intermediate_result)
                self.current_expression = result
            except Exception:
                self.current_expression = "Error"
        else:
             if self.current_expression == "Error":
                 self.current_expression = ""
             self.current_expression += label
        
        self.display.set_text(self.current_expression)

    def on_key_pressed(self, controller, keyval, keycode, state):
        key_map = {
            Gdk.KEY_0: '0', Gdk.KEY_KP_0: '0',
            Gdk.KEY_1: '1', Gdk.KEY_KP_1: '1',
            Gdk.KEY_2: '2', Gdk.KEY_KP_2: '2',
            Gdk.KEY_3: '3', Gdk.KEY_KP_3: '3',
            Gdk.KEY_4: '4', Gdk.KEY_KP_4: '4',
            Gdk.KEY_5: '5', Gdk.KEY_KP_5: '5',
            Gdk.KEY_6: '6', Gdk.KEY_KP_6: '6',
            Gdk.KEY_7: '7', Gdk.KEY_KP_7: '7',
            Gdk.KEY_8: '8', Gdk.KEY_KP_8: '8',
            Gdk.KEY_9: '9', Gdk.KEY_KP_9: '9',
            Gdk.KEY_period: '.', Gdk.KEY_KP_Decimal: '.',
            Gdk.KEY_plus: '+', Gdk.KEY_KP_Add: '+',
            Gdk.KEY_minus: '-', Gdk.KEY_KP_Subtract: '-',
            Gdk.KEY_asterisk: '×', Gdk.KEY_KP_Multiply: '×',
            Gdk.KEY_slash: '÷', Gdk.KEY_KP_Divide: '÷',
            Gdk.KEY_Return: '=', Gdk.KEY_KP_Enter: '=', Gdk.KEY_equal: '=',
            Gdk.KEY_BackSpace: '←',
            Gdk.KEY_Escape: 'C',
            Gdk.KEY_c: 'C', Gdk.KEY_C: 'C',
        }

        # Check for Quit shortcuts (Ctrl+Q, Ctrl+W)
        if state & Gdk.ModifierType.CONTROL_MASK:
            if keyval == Gdk.KEY_q or keyval == Gdk.KEY_w:
                self.close()
                return True

        if keyval in key_map:
            label = key_map[keyval]
            self.on_button_clicked(None, label)
            return True
        
        return False

class CalculatorApp(Gtk.Application):
    def __init__(self):
        super().__init__(application_id="org.jordanblakey.invisicalc.v1",
                         flags=Gio.ApplicationFlags.FLAGS_NONE)

    def do_activate(self):
        win = self.props.active_window
        if not win:
            win = CalculatorWindow(self)
        win.present()

if __name__ == '__main__':
    app = CalculatorApp()
    app.run(sys.argv)
