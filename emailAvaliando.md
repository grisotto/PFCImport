### Análise ARE e STD 200x200

#### Predominância tipo linha

####**rodovia** 
- **ARE** -- teve melhora entre 0,52 - 0,88.
- **STD** -- teve melhora entre 0,50 - 0,94. Em qualquer divisão.


####**railways** 
- **ARE** -- teve melhora entre 0,52 - 0,62
- **STD** -- teve melhora entre 0,52 - 0,62


Observando datasets com objetos tipo linha: **elevcontour**, **roads**, **hidrografia ** - não tiveram melhora e até piora.

No caso do **roads**, teve um piora significativa.

Para o dataset **hydroinland** o método nem identificou alguma col/linha para fazer o merge.

#### Predominância tipo polígnos

####**vegeta** 
- **ARE** -- teve melhora entre 0,90 - 0,94
- **STD** -- teve melhora entre 0,50 - 0,94. Em qualquer divisão.


####**municipios**
- **ARE** -- não ficou claro, pois teve melhoras e pioras. As melhoras foram 0,50 - 0,58; 0,72; 0,84; 0,88 - 0,94
- **STD** -- teve melhora entre 0,50 - 0,94. Em qualquer divisão.


**Crops** - praticamente nao teve alteração.
O dataset tipo poligno **alerta** o método não identificou alguma col/linha para fazer o merge.


O dataset **charminar** que é tipo ponto o método não identificou alguma col/linha para fazer o merge.




#### 1. Easier to run, manage and extend/maintain:

- just generate and edit a Guardfile (once) and run `guard`
- nice, readable [DSL](https://github.com/guard/guard/wiki/Guardfile-DSL---Configuring-Guard) for setting complex rules
- in Ruby
- simple example templates are generated for you
- well documented, lots of simple examples
- fantastic community support (just file an issue and see...)
- built-in support for logging and notification (Growl, etc.)


#### 2. more efficient:

- allows efficiently talking with servers (connect once on startup, then make a request every change)
- scans large directories only once on startup
- no "sleep" code needed - changes can happen either immediately, or they can be "accumulated" and "compressed" (to avoid running the command too frequently)


#### 3. more robust and "correct":

- properly handled cases when files are changed while the command is running
- no inotifywait/inotifywatch errors to deal with
- watches the files directory, so it supports file adding, renames (which is what editors do - they rarely just "modify" a file in place)
- interactive console to rerun, simulate and debug events
- Guard itself reloads when you change its configuration
- a single instance of Guard can handle many directories (instead of running many unmanageable "instances" of inotify_wait scripts running)
- more than 7 million gem downloads and almost no open issues
- handles moving whole files and directories

#### 4. more portable:

- supports multiple platforms (Linux, OSX, BSD, Windows)
- supports multiple backends (inotify, kqueue, polling)
- polling for network drives and VM shared dirs (which don't support inotify)

