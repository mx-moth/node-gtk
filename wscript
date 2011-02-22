srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.check_cfg(package='gtk+-2.0', uselib_store='GTK', args='--cflags --libs')
  conf.check_cfg(package='glib-2.0', args='--cflags --libs', uselib_store='GLIB')

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon", uselib = 'GTK')
  obj.cxxflags = ["-Wall", "-ansi", "-pedantic", "-std=c++0x"]
  obj.target = "gtk"
  obj.source = """
               src/gtk.cc
               src/g_object.cc
               src/gtk_object.cc
               src/gtk_widget.cc
               src/gtk_bin.cc
               src/gtk_container.cc
               src/gtk_window.cc
               src/gtk_box.cc
               src/gtk_hbox.cc
               src/gtk_vbox.cc
               src/gtk_button.cc
               src/gtk_entry.cc
               src/gtk_misc.cc
               src/gtk_label.cc
               src/gtk_tree_store.cc
               src/gtk_tree_iter.cc
               src/gtk_tree_view.cc
               src/gtk_tree_view_column.cc
               src/gtk_cell_renderer.cc
               src/gtk_cell_renderer_text.cc
               src/gtk_cell_renderer_toggle.cc
               """
  obj.uselib = "GTK GLIB"
