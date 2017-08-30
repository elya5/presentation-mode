pm_sources = [
  'main.c',
  'presentationmodeapp.h',
  'presentationmodeapp.c',
  'presentationmodeappwin.h',
  'presentationmodeappwin.c',
  'pm-save-restore.h',
  'pm-save-restore.c',
  pm_resources
]

pm_deps = [
  dependency('glib-2.0'),
  dependency('gtk+-3.0'),
]

executable('presentation-mode', pm_sources,
  dependencies: pm_deps,
  install: true,
)
