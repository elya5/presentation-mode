gnome = import('gnome')

pkgdatadir = join_paths(get_option('prefix'), get_option('datadir'), meson.project_name())
datadir = join_paths(get_option('prefix'), get_option('datadir'))
desktopdir = join_paths (datadir, 'applications')

pm_resources = gnome.compile_resources(
  'resources',
  'de.flump.presentation-mode.gresources.xml',
  c_name: '_presentation_mode',
  source_dir: 'src'
)

install_data('de.flump.presentation-mode.svg',
             install_dir: join_paths([datadir,'icons/hicolor/scalable/apps']))

install_data('de.flump.presentation-mode.desktop',
             install_dir: desktopdir)
