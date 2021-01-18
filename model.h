struct friendList {
    char username[25];
    friendList *next, *prev;
};

struct friendInbox {
    char username[25];
    friendInbox *next, *prev;
};

struct friendReq {
    char username[25];
    friendReq *next, *prev;
};

struct commentNotes {
    char username[25];
    char comment[255];
    commentNotes *next, *prev;
};

struct recycleBin {
    char title[25];
    char content[255];
    char category[25];
    recycleBin *next, *prev;
};

struct note {
    char title[25];
    char content[255];
    char category[25];
    note *next, *prev;
};

struct userList {
    char username[25];
    char password[25];
    friendList *headFriendList, *tailFriendList;
    friendInbox *headFriendInbox, *tailFriendInbox;
    friendReq *headFriendReq, *tailFriendReq;
    note *headNote, *tailNote;
    recycleBin *headRecycleBin, *tailRecycleBin;
    userList *next, *prev;
} *headUser, *tailUser;

struct privateFriend {
    char username[25];
    privateFriend *next, *prev;
};

struct publicDashboard {
    char username[25];
    char title[25];
    char content[255];
    char category[25];
    int like;
    bool privateOrPublic;
    privateFriend *headPrivate, *tailPrivate;
    commentNotes *headComment, *tailComment;
    publicDashboard *next, *prev;
} *headPd, *tailPd;