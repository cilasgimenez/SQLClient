//
//  SQLClient.h
//  SQLClient
//
//  Created by Martin Rybak on 10/4/13.
//  Copyright (c) 2013 Martin Rybak. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString* _Nonnull const SQLClientMessageNotification;
extern NSString* _Nonnull const SQLClientErrorNotification;
extern NSString* _Nonnull const SQLClientMessageKey;
extern NSString* _Nonnull const SQLClientCodeKey;
extern NSString* _Nonnull const SQLClientSeverityKey;

/**
 *  Native SQL Server client for iOS. An Objective-C wrapper around the open-source FreeTDS library.
 */
@interface SQLClient : NSObject

/**
 *  Connection timeout, in seconds. Default is 5. Set before calling connect.
 */
@property (nonatomic, assign) int timeout;

/**
 *  The character set to use for converting the UCS-2 server results. Default is UTF-8.
 *  Set before calling connect. Can be set to any charset supported by the iconv library.
 *  To list all supported iconv character sets, open a Terminal window and enter:
 $  iconv --list
 */
@property (nonatomic, copy, nonnull) NSString* charset;

/**
 *  The maximum text size to use for NVARCHAR(MAX) and TEXT data types. Default is 4096.
 *  Execute SELECT @@TEXTSIZE to determine the current setting on the server and use
 *  the result to update this property.
 */
@property (atomic, assign) int maxTextSize;

/**
 *  Returns an initialized SQLClient instance as a singleton.
 *
 *  @return Shared SQLClient object
 */
+ (nullable instancetype)sharedInstance;

/**
 *  Connects to a SQL database server.
 *
 *  @param host     Required. The database server, i.e. server, server:port, or server\instance (be sure to escape the backslash)
 *  @param username Required. The database username
 *  @param password Required. The database password
 *  @param database The database name
 *  @param completion Block to be executed upon method successful connection
 */
- (void)connect:(nonnull NSString*)host
       username:(nonnull NSString*)username
       password:(nonnull NSString*)password
       database:(nullable NSString*)database
     completion:(nullable void(^)(BOOL success))completion;

/**
 *  Indicates whether the database is currently connected.
 */
- (BOOL)isConnected;

/**
 *  Indicates whether the database is executing a command.
 */
- (BOOL)isExecuting;

/**
 *  Returns the maximum text size configured on the server (default 4096).
 */
- (int)maxTextSize;

/**
 *  Executes a SQL statement. Results of queries will be passed to the completion handler. Inserts, updates, and deletes do not return results.
 *
 *  @param sql Required. A SQL statement
 *  @param completion Block to be executed upon method completion. Accepts an NSArray of tables. Each table is an NSArray of rows.
 *  Each row is an NSDictionary of columns where key = name and object = value as one of the following types:
 *  NSString, NSNumber, NSDecimalNumber, NSData, UIImage, NSDate, NSUUID
 */
- (void)execute:(nonnull NSString*)sql completion:(nullable void(^)(NSArray* _Nullable results))completion;

/**
 *  Disconnects from database server.
 */
- (void)disconnect;

@end
