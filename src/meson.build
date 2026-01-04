invisicalc_sources = [
  'main.c',
  'invisicalc-application.c',
  'invisicalc-window.c',
]

invisicalc_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
  m_dep,
]

blueprint_compiler = find_program('blueprint-compiler', required: true)

blueprints = custom_target('blueprints',
  input: 'main.blp',
  output: 'main.ui',
  command: [blueprint_compiler, 'compile', '--output', '@OUTPUT@', '@INPUT@'],
)

invisicalc_sources += gnome.compile_resources('invisicalc-resources',
  'invisicalc.gresource.xml',
  c_name: 'invisicalc',
  dependencies: blueprints
)

executable('invisicalc', invisicalc_sources,
  dependencies: invisicalc_deps,
       install: true,
)
