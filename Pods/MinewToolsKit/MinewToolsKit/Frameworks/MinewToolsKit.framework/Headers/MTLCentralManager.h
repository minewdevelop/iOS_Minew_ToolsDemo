//
//  MTLCentralManager.h
//  MinewSensorKit
//
//  Created by Minewtech on 2019/8/5.
//  Copyright © 2019 Minewtech. All rights reserved.
//

#import <Foundation/Foundation.h>
@class MTLPeripheral,CBCentralManager;

// iphone bluetooth state, this sdk works well only in poweron state
typedef NS_ENUM(NSUInteger, MTLPowerState) {
    PowerStateUnknown = 0,
    PowerStatePoweredOff,
    PowerStatePoweredOn,
};

// get scanned devices in this block
typedef void(^MTLScanBlock)(NSArray<MTLPeripheral *> *peripherals);

typedef void(^MTLPasswordRequireBlock)(NSString *password);

typedef void(^BluetoothChangeCompletion)(MTLPowerState status);

@interface MTLCentralManager : NSObject

// current iphone bluetooth state
@property (nonatomic, assign) MTLPowerState state;

// current scanned devices
@property (nonatomic, strong, readonly) NSArray<MTLPeripheral *> *scannedPeris;

/**
 get shared MTLCentralManager instance
 
 @return MTLC instance
 */
+ (instancetype)sharedInstance;


/**
 start scan devices,
 get scanned devices in handler block or "scannedPeris" property.
 
 @param handler listen scanned devices
 */
- (void)startScan:(MTLScanBlock)handler;

// start scan
- (void)startScan;

// stop scanning
- (void)stopScan;

/**
 try connect to a MTLperipheral instance.
 
 @param per MTLPeripheral instance wanted to be connected
 */
- (void)connectToPeriperal:(MTLPeripheral *)per;

/**
 disconnect from a MTLperipheral instance.
 
 @param per MTLPeripheral instance wanted to be disconnected.
 */
- (void)disconnectFromPeriperal:(MTLPeripheral *)per;


/**
 a callback for iphone bluetooth changes.
 
 @param completionHandler the bluetooth status changes block.
 */
- (void)didChangesBluetoothStatus:(BluetoothChangeCompletion)completionHandler;

@end
