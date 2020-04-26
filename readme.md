<!DOCTYPE html>
<html lang="en">
<!-- header -->
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1">
<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
<!--<link rel="icon" href="favicon.ico"/>-->
<!-- bootstrap -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous"/>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css" integrity="sha384-fLW2N01lMqjakBkx3l/M9EahuwpSfeNvV63J5ezn3uZzapT0u7EYsXMjQV+0En5r" crossorigin="anonymous"/>
<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<link href="/~chuang/lib/theme/ie10-viewport-bug-workaround.css" rel="stylesheet"/>
<!-- font awesome -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
<!-- custom bootstrap theme -->
<link href="/~chuang/lib/theme/theme.css" rel="stylesheet">
<link href="/~chuang/lib/theme/callout.css" rel="stylesheet">
<link href="/~chuang/lib/custom.css" rel="stylesheet">
<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
<!--[if lt IE 9]>
  <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
  <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
<![endif]-->
<style></style>
<title>Chun-Ying Huang</title>
<style>
code {
	margin: 8px 0;
	white-space: pre;
	display: block;
}
.term {
	font-family: monospace;
	font-weight: bold;
	display: inline-block;
	width: 12%;
}
.texttt {
	font-family: monospace;
	font-weight: bold;
}
em {
	color: blue;
}
</style>
</head>
<!-- body -->
<body role="document">
<!-- Fixed navbar -->
<nav class="navbar navbar-inverse navbar-fixed-top">
<div class="container">
<div class="navbar-header">
	<!-- for mobile toggle button -->
	<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
		<span class="sr-only">Toggle navigation</span>
		<span class="icon-bar"></span>
		<span class="icon-bar"></span>
		<span class="icon-bar"></span>
	</button>
	<!--<a class="navbar-brand">Chun-Ying Huang</a>-->
	<a class="navbar-brand"><img src="/~chuang/images/n_all.png" style="border: none"/></a>
</div>
<div id="navbar" class="navbar-collapse collapse">
	<ul class="nav navbar-nav">
	<li><a href="/~chuang/">Home</a></li>
	<li><a href="/~chuang/students.php">Students</a></li>
	<!--<li><a href="projects.php">Projects</a></li>-->
	<li><a href="/~chuang/pubs.php">Publications</a></li>
	<li class="dropdown active">
	<a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">Courses <span class="caret"></span></a>
		<ul class="dropdown-menu">
		<!--<li role="separator" class="divider"></li>
		<li class="dropdown-header">Courses</li>-->
		<li><a href="/~chuang/courses/unixprog/">UNIX Programming</a></li>
		<li><a href="/~chuang/courses/softdev/">Software Development Practice</a></li>
		<li><a href="/~chuang/courses/swsec/">Software Security (Secure Programming)</a></li>
		<!--<li><a href="#">Another action</a></li>
		<li><a href="#">Something else here</a></li>
		<li role="separator" class="divider"></li>
		<li class="dropdown-header">External resources</li>
		<li><a href="#">Separated link</a></li>
		<li><a href="#">One more separated link</a></li>-->
		</ul>
	</li>
	</ul>
</div><!--/.nav-collapse -->
</div>
</nav>
<!-- main body -->
<div class="container theme-showcase" role="main">

<h3>Homework #2</h3>
<h4><small>Advanced Programming in the UNIX Environment</small></h4>

<h4>Due: May 11, 2020</h4>

<h3>Play in a Sandbox!?</h3>

<p>In this homework, we are going to practice library injection and API hijacking. Please implement a sandbox that confines file relevant operations to a user provided directory. You have to implement your sandbox as a <u>shared library (1)</u> (e.g., sandbox.so) and then inject the shared library into a process using using your customized <u>command launcher (2)</u> (e.g., sandbox). If an operation attempts to escape from the sandbox, e.g., open a file or a directory outside the sandbox, you have to reject the request by returning an error code to the function caller. In addition, please also output an error message to the user's <u>terminal</u>. You should output error messages correctly even if the command line has redirected outputs/errors to a file. Please check the functions listed in the section "Requirements" below.</p>

<p>You have to compile your source codes and generate 1) the shared object and 2) the launcher. You don't have to implement any test program by yourself. Instead, you have to work with those binaries already installed in the system.</p>

<h3>Requirements</h3>

<p>The list of monitored library calls is shown below. It covers several functions we have introduced in the class.
<div class="term">chdir</div>
<div class="term">chmod</div>
<div class="term">chown</div>
<div class="term">creat</div>
<div class="term">fopen</div>
<div class="term">link</div>
<div class="term">mkdir</div>
<div class="term">open</div>
<div class="term">openat</div>
<div class="term">opendir</div>
<div class="term">readlink</div>
<div class="term">remove</div>
<div class="term">rename</div>
<div class="term">rmdir</div>
<div class="term">stat</div>
<div class="term">symlink</div>
<div class="term">unlink</div>
</p>

<p>In addition to the aforementioned library calls, your sandbox ALWAYS has to reject the use of the following functions:
<div class="term">execl</div>
<div class="term">execle</div>
<div class="term">execlp</div>
<div class="term">execv</div>
<div class="term">execve</div>
<div class="term">execvp</div>
<div class="term">system</div>
</p>

<h3>Output Messages</h3>

<p>If an invalid access is detected, your program has to output an error message to indicate the error. If an access to an invalid path is detected, please show the target pathname and the corresponding operation. If the use of <code style="display: inline">system</code> or <code style="display: inline">exec*</code> is rejected, please also show the function name and the command line (for system) or the executable name (for exec*).
</p>

<h3>Grading Policy</h3>

<p>The grading policy for this homework is listed below:
<ul>
<li>[10%] Use Makefile to manage the building process of your program. <span style="color:red">We will not grade your program if we cannot use <b>make</b> command to build your program.</span></li>
<li>[30%] A sandboxed executable can work as usual. Your program cannot change the behavior of a sandboxed executable if the accesses are in the allowed base directory and its subdirectories.</li>
<li>[30%] Implement file/directory-relevant functions listed in the requirements.</li>
<li>[20%] Implement <code style="display: inline">system</code> and <code style="display: inline">exec*</code> functions listed in the requirements.</li>
<li>[10%] Display error messages.</li>
</ul>
</p>

<h3>Homework Submission</h3>

<p>Please pack your files into a single <span style="color: red">tar.gz</span> archive and submit your homework via the system. Please also provide a <span style="color: red">Makefile</span> (used for compiling and linking your codes) and a <span style="color: red">README</span> file (indicating what functions will be monitored) in your archive.</p>

<h3>Hints</h3>

<p>Some hints that may simplify your work:
<ol>
<li>We will test your program on Ubuntu 18.04. For the best compatibility, you may develop your program on Ubuntu 18.04.</li>
<li>You may need to define macros to simplify your implementation.</li>
<li>You may consider working with # and ## operators in macros.</li>
<li>For variable-length function parameters, consider working with <a href="http://man7.org/linux/man-pages/man0/stdarg.h.0p.html" target="_blank">stdarg.h</a>.</li>
<li>You may consider working with <span class="texttt">__attribute__((constructor))</span>. If you don't know what is that, please google for it!</li>
<li>The implementation for some library functions may be different from its well-known prototypes. For example, the actual implementation for <b>stat</b> in GNU C library is <b>__xstat</b>. Therefore, you may be not able to find symbol <b>stat</b> in the binary. In case that you are not sure about the <em>real</em> symbols used in C library, try to work with <b>readelf</b> or <b>nm</b> to get the symbol names.</li>
<li>Sample macro implementation is available <a href="macro.txt">here</a>.</li>
<li>You may use <code style="display: inline">ltrace</code> command to check what library functions are called by a program.</li>
</ol>
</p>

<h4>Running Examples</h4>

<p>Suppose you have compiled your homework files into <b>sandbox.so</b> and your launcher files into <b>sandbox</b>, respectively, several examples from our simple implementation are given below.</p>

<p style="color: red">NOTE: the sample program only implements parts of listed function. The output of the following sample messages are simply for demonstration purpose. The actual functions captured by your sandbox may be different depending on the completeness of your implementation and the runtime environment.</p>

<code><em># default message</em>
$ ./sandbox
no command given.

<em># show help message ...</em>
$ ./sandbox -h
./sandbox: invalid option -- 'h'
usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]
        -p: set the path to sandbox.so, default = ./sandbox.so
        -d: the base directory that is allowed to access, default = .
        --: separate the arguments for sandbox and for the executed command

<em># the regular 'ls' command</em>
$ ls
Makefile  sandbox  sandbox.c  sandbox.so  sandboxso.c

<em># sandboxed 'ls' command</em>
$ ./sandbox ls
Makefile  sandbox  sandbox.c  sandbox.so  sandboxso.c

<em># pass -a to 'ls' command: bad example</em>
$ ./sandbox ls -a
./sandbox: invalid option -- 'a'
usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]
        -p: set the path to sandbox.so, default = ./sandbox.so
        -d: the base directory that is allowed to access, default = .
        --: seperate the arguments for sandbox and for the executed command

<em># pass -a to 'ls' command</em>
$ ./sandbox -- ls -a
.  ..  .gdb_history  Makefile  sandbox  sandbox.c  sandbox.so  sandboxso.c

<em># the regular 'ls /' command</em>
$ ls /
bin   data  etc   lib    lib64   lost+found  mnt  proc  root  sbin  snap  sys  usr  vmlinuz
boot  dev   home  lib32  libx32  media       opt  repo  run   sh    srv   tmp  var  vmlinuz.old

<em># sandboxed 'ls /' command</em>
$ ./sandbox -- ls /
[sandbox] opendir: access to / is not allowed
ls: cannot open directory '/'

<em># sandboxed 'ls /' command: access granted by -d</em>
$ ./sandbox -d / ls /
bin   data  etc   lib    lib64   lost+found  mnt  proc  root  sbin  snap  sys  usr  vmlinuz
boot  dev   home  lib32  libx32  media       opt  repo  run   sh    srv   tmp  var  vmlinuz.old

<em># another sandboxed output</em>
$ ./sandbox -- ls -la / Makefile
-rw-rw-r--  1 chuang chuang  224 Oct 27 21:13 Makefile

[sandbox] opendir: access to / is not allowed
ls: cannot open directory '/'

<em># redirect output to /dev/null</em>
$ ./sandbox -- ls -la / Makefile &gt;/dev/null
[sandbox] opendir: access to / is not allowed
ls: cannot open directory '/'

<em># redirect output and error to /dev/null: this is an optional feature</em>
$ ./sandbox -- ls -la / Makefile &gt;/dev/null 2&gt;&amp;1
[sandbox] opendir: access to / is not allowed

<em># execve is always not allowed ...</em>
<em># NOTE: this sample does not implement `open' and `stat' functions ...</em>
$ ./sandbox -- sh -c 'ls'
[sandbox] execve(/bin/ls): not allowed
[sandbox] execve(/usr/games/ls): not allowed
[sandbox] execve(/usr/local/games/ls): not allowed
[sandbox] execve(/snap/bin/ls): not allowed
sh: 1: ls: Permission denied

<em># execve is always not allowed ...</em>
<em># NOTE: this sample implements `open' and `stat' functions ...</em>
$ ./sandbox -- sh -c 'ls'
[sandbox] open: access to /dev/tty is not allowed
[sandbox] open: access to /dev/pts/2 is not allowed
[sandbox] __xstat: access to /usr/local/sbin/sh is not allowed
[sandbox] __xstat: access to /usr/local/bin/sh is not allowed
[sandbox] __xstat: access to /usr/bin/sh is not allowed
[sandbox] fopen: access to /etc/passwd is not allowed
[sandbox] __xstat: access to /usr/local/sbin/ls is not allowed
[sandbox] __xstat: access to /usr/local/bin/ls is not allowed
[sandbox] __xstat: access to /usr/bin/ls is not allowed
sh: ls: command not found

</code>

<h4>Some Other Hints ...</h4>

<p>When testing your homework, you may inspect symbols used by an executable. We have mentioned that you are not able to see any symbol if the symbols were stripped using <b>strip</b> command. However, you may consider working with <b>readelf</b> command. For example, we can check the symbols that are unknown to the binary:</p>

<code>$ nm /usr/bin/wget
nm: /usr/bin/wget: no symbols
$ readelf --syms /usr/bin/wget | grep open
    72: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND freopen64@GLIBC_2.2.5 (2)
    73: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND iconv_open@GLIBC_2.2.5 (2)
   103: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND gzdopen
   107: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND fdopen@GLIBC_2.2.5 (2)
   119: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND open64@GLIBC_2.2.5 (2)
   201: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND fopen64@GLIBC_2.2.5 (2)</code>

<p>Alternatively, you may consider using <b>nm -D</b> to read symbols.</p>

<p>To simplify the process to find real symbol names, you may compile the <a href="sample.c">sample program</a> with the following two commands, and check the dynamic linkage symbols in the corresponding executables.

<code><em># regular version</em>
$ gcc sample.c -o sample1

<em># enable large-file-support feature</em>
$ gcc sample.c -o sample2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
</code></p>


</div><!-- container -->
<footer class="footer">
	<div class="container">
	<hr/>
	<p><small>&copy; 2008&mdash;2020 Chun-Ying Huang, Security and Systems Laboratory, Department of Computer Science, National Chiao Tung University.</small></p>
	</div>
</footer>
<script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-75749309-1', 'auto');
  ga('send', 'pageview');

</script>
<!-- Placed at the end of the document so the pages load faster -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS" crossorigin="anonymous"></script>
<!--<script src="lib/theme/docs.min.js"></script>-->
<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<script src="/~chuang/lib/theme/ie10-viewport-bug-workaround.js"></script>
</body>
</html>