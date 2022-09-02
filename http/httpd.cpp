//
// Created by sjhuang on 2022/8/20.
//

#include "httpd.h"

httpd::httpd() {
    memset(buffer, 0, READ_BUFFER_SIZE);
    cur_buffer_idx = 0;
}

// ET 模式下，要将缓冲区读取完毕
// LT 模式下，读取一次就可以了
// TODO, 这里有可能存在请求占据过大，有可能缓冲区被读满，然后发生错误
bool httpd::read_once() {
    if(cur_buffer_idx >= READ_BUFFER_SIZE){
        return false;
    }
    int bytes_read = 0;
    // ET 模式
    while(true){
        bytes_read = recv(sockfd, buffer + cur_buffer_idx,READ_BUFFER_SIZE - cur_buffer_idx, 0);
        if(bytes_read == -1){
            // 读取完毕
            if(errno == EAGAIN || errno == EWOULDBLOCK) break;
            // 出错，返回错误
            return false;
        }else if(bytes_read == 0) return false; // 收到关闭
        cur_buffer_idx += bytes_read;
    }
    return true;
}

void httpd::init(int sockfd, const sockaddr_in &addr) {
    this->sockfd = sockfd;
    this->addr = addr;
}

// 读取一行
char * httpd::get_line(){
    return buffer + m_start_line;
}

//从状态机，用于分析出一行内容
//返回值为行的读取状态，有LINE_OK,LINE_BAD,LINE_OPEN
LINE_STATUS httpd::parse_line() {
    char tmp;
    for(; m_checked_idx < cur_buffer_idx; ++ m_checked_idx){
        tmp = buffer[m_checked_idx];
        if(tmp == '\r'){
            if((m_checked_idx + 1) == cur_buffer_idx){
                return LINE_OPEN;
            }else if(buffer[m_checked_idx + 1] == '\n'){
                buffer[m_checked_idx++] = '\0';
                buffer[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }else if(tmp == '\n'){
            if(m_checked_idx > 1 && buffer[m_checked_idx - 1] == '\r'){
                buffer[m_checked_idx - 1] = '\0';
                buffer[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}


HTTP_CODE httpd::parse_request_line(char *text){
    vector<string> items = split(text, '\t');
    int k = items.size();
    if(k != 3){
        return BAD_REQUEST;
    }
    if(items[0] == "GET"){
        m_method = GET;
    }else if(items[0] == "POST"){
        m_method = POST;
    }else{
        // TODO 其它请求方法
        return BAD_REQUEST;
    }
    // TODO
    m_url = items[1];
    m_version = items[2];
    if(m_version != "HTTP/1.1"){
        // TODO 其它HTTP版本
        return BAD_REQUEST;
    }
    parse_status = PARSE_HEADER;
    return NO_REQUEST;
}


HTTP_CODE httpd::parse_header_line(char *text) {
    if(text[0] == '\0'){
        if(head_params.count("Content-length") && head_params["Content-length"] > "0"){
            parse_status = PARSE_CONTEXT;
        }
        return NO_REQUEST;
    }
    vector<string> kvs = split(text, ':');
    if(kvs.size() != 2){
        return BAD_REQUEST;
    }
    head_params[kvs[0]] = kvs[1];
    return NO_REQUEST;
}

HTTP_CODE httpd::parse_content(char *text) {
    if(head_params.count("Content-length") && head_params["Content-length"] > "0"){
        const char *cl = head_params["Content-length"].c_str();
        int content_length = atoi(cl);
        if(cur_buffer_idx >= (content_length + m_checked_idx)){
            m_string = text;
            return GET_REQUEST;
        }
    }
    return NO_REQUEST;
}

void httpd::parse() {
    // 从 fd 中读取
    int buffer_size = 4096;
    char buf[buffer_size];
    int n = 0;
    string prev = "", cur = "";
    PARSE_STATUS status = PARSE_METHOD;
    while(true){
        // 有一个 '\0'
        n = recv(sockfd, buf, buffer_size - 1, 0);
        if(n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)){
            break;
        }else if(n < 0){
            throw std::exception();
        }
        // 解析 parse method
        cur =  cur + string(buf);
        if(status == PARSE_METHOD){
            parse_header_line(cur);
        }else if(status == PARSE_HEADER){

        }else if(status == PARSE_CONTEXT){

        }else{

        }
    }
}

void httpd::parse_method(string str){
    vector<string> items = split(str, '\r');
}