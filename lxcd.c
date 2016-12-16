/* 
 *  lxcd - a daemon to control host and containers
 */


#define SOCKET_PATH "/dev/socket/lxcd"
#define LOG_TAG "LXCD"
#define LXCD_LOG(...)


int lxcd_open_socket(){
//    if(open(SOCKET_PATH)){
//        //error
//    }
     return -1;
}
int do_switch_stuff(){
    LXC_LOG("IF YOU SEE THIS ,EVERYTHING ELSE REAL LXC COMMAND IS READY\n");
    return 0;
}

int main(const int argc, const char *argv[]) {
    int fd/*socker fd*/ ,s/*incoming connection*/;
    struct sockaddr addr;
    socklen_t alen;    
    if( (fd=lxcd_open_socket())<0 ){    //open a unix datagam socket
        LXCD_LOG("open sockete failed (%s)\n",strerror(errno));
        exit(1);
    }
    if( listen(fd,1) ){
        LXCD_LOG("listen failed (%s)",strerror(errno));
        exit(1);
    }
    fcntl(fd, F_SETFD, FD_CLOEXEC);    //close on exec

    for(;;){
        alen = sizeof(addr);
        s = accept(fd, &addr, &alen);
        if (s < 0) {
            LXCD_LOG("Accept failed: %s\n", strerror(errno));
            continue;
        }
        fcntl(s, F_SETFD, FD_CLOEXEC);
        LXCD_LOG("new connction\n");
        for(;;){
            char value;
            if( read(s,&value,sizeof(value) != sizeof(value) ){
                LXCD_LOG("failed to read\n");
                break;
            }
            if(value!=0){   //I expect client to write single byte \0
                LXCD_LOG("read wrong value (%d)\n",value);
                break;
            }

            /* all..right, do some real business */
            do_switch_stuff();

        }
        LXC_LOG("closing connectoin\n");
        close(s);
    }     
}

