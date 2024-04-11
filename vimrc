" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" runtime! debian.vim

" Vim will load $VIMRUNTIME/defaults.vim if the user does not have a vimrc.
" This happens after /etc/vim/vimrc(.local) are loaded, so it will override
" any settings in these files.
" If you don't want that to happen, uncomment the below line to prevent
" defaults.vim from being loaded.
" let g:skip_defaults_vim = 1

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
set nocompatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
if has("syntax")
  syntax on
endif

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
filetype plugin indent on

" Disable the default Vim startup message
set shortmess+=I

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
set showmatch		" Show matching brackets.
set ignorecase		" Do case insensitive matching
set smartcase		" Do smart case matching
set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
set hidden		" Hide buffers when they are abandoned
set mouse+=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

set relativenumber
setlocal noswapfile		" 不要生成swap文件
set bufhidden=hide		" 当buffer被丢弃的时候隐藏它
"colorscheme evening	" 设定配色方案
set number						" 显示行号
" set cursorline				" 突出显示当前行
set ruler							" 打开状态栏标尺
set shiftwidth=2			" 设定 << 和 >> 命令移动时的宽度为 2
set softtabstop=2			" 使得按退格键时可以一次删掉 2 个空格
set tabstop=2					" 设定 tab 长度为 2
set nobackup					" 覆盖文件时不备份
set autochdir					" 自动切换当前目录为当前文件所在的目录
set backupcopy=yes		" 设置备份时的行为为覆盖
set hlsearch					" 搜索时高亮显示被找到的文本
set noerrorbells visualbell t_vb=			" 关闭错误信息响铃
set novisualbell			" 关闭使用可视响铃代替呼叫
set t_vb=							" 置空错误铃声的终端代码
set matchtime=2				" 短暂跳转到匹配括号的时间
set magic							" 设置魔术
set smartindent				" 开启新行时使用智能自动缩进
set backspace=indent,eol,start " 不设定在插入状态无法用退格键和 Delete 键删除回车符
set cmdheight=1				" 设定命令行的行数为 1
set laststatus=2			" 显示状态栏 (默认值为 1, 无法显示状态栏)
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ %{&encoding}\ Ln\ %l,\ Col\ %c/%L%) " 设置在状态行显示的信息
set foldenable				" 开始折叠
set foldmethod=syntax " 设置语法折叠
set foldcolumn=0 " 设置折叠区域的宽度
setlocal foldlevel=1 " 设置折叠层数为 1
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<CR> " 用空格键来开关折叠
nmap Q <Nop> " 'Q' in normal mode enters Ex mode. You almost never want this.


filetype off								" required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'

" All of your Plugins must be added before the following line
call vundle#end()						" required
filetype plugin indent on		" required

" nerdtree
" autocmd vimenter * NERDTree		" 打开im，自动开启nerd tree
map <F3> :NERDTreeMirror<CR>	" 通过F3打开/关闭nerd tree

" CtrlP
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
