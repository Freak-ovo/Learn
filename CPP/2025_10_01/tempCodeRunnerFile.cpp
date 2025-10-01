    //第一种
    char buf[1024] = {0};
    while (ifs >> buf)
    {
        cout << buf << endl;
    }