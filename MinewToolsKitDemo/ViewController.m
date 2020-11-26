//
//  ViewController.m
//  MinewToolsKitDemo
//
//  Created by minew on 2020/10/15.
//

#import "ViewController.h"
#import <MinewToolsKit/MinewToolsKit.h>
#import "DeviceVC.h"

@interface ViewController ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) MTLCentralManager *manager;

@property (nonatomic, strong) NSArray<MTLPeripheral *> *scanPeripherals;

@property (nonatomic, strong) UITableView *tableView;


@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.title = @"Devices";
    // Get Manager instance
    _manager = [MTLCentralManager sharedInstance];
    [self scan];
    [self initViews];
    
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(reloadTableView) userInfo:nil repeats:YES];

}

- (void)reloadTableView {
    self.scanPeripherals = self.manager.scannedPeris;
    [self.tableView reloadData];
}

// Scan Device
- (void)scan {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        // bluetooth status
        if(self->_manager.state == PowerStatePoweredOn) {
            // start scan
            [self->_manager startScan:^(NSArray<MTLPeripheral *> *peripherals) {
                self->_scanPeripherals = peripherals;
            }];
        }
    });
    //Scanned devices can also be obtained using manager.scannedPeris

    //If you need to respond to the Bluetooth status of the phone. Please listen for callback.
    [_manager didChangesBluetoothStatus:^(MTLPowerState statues) {
        
        switch(statues) {
            case PowerStatePoweredOn:
                NSLog(@"bluetooth status change to poweron");
                break;
            case PowerStatePoweredOff:
                NSLog(@"bluetooth status change to poweroff");
                break;
            case PowerStateUnknown:
                NSLog(@"bluetooth status change to unknown");
        }
    }];
}

// Connect Device
- (void)connectPeripheral:(MTLPeripheral *)peripheral {
    // Connect to device
    [_manager connectToPeriperal:peripheral];
    // Monitor device connection status
    [peripheral.connector didChangeConnection:^(MTLConnection connection) {
        
        if (connection == Vaildated) {
              //The verification is successful and the device is successfully connected.
            NSLog(@"vaildated");
              //Perform other operations after successful verification.
            [self pushDeviceVCWithPeripheral:peripheral];
        }
        if (connection == Disconnected) {
            NSLog(@"device has disconnected.");
        }
    }];
}

- (void)pushDeviceVCWithPeripheral:(MTLPeripheral *)peripheral {
    DeviceVC *vc = [[DeviceVC alloc] init];
    vc.manager = self.manager;
    vc.peripheral = peripheral;
    [self.navigationController pushViewController:vc animated:YES];
}

// MARK: - UITableView DataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.scanPeripherals.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    
    MTLPeripheral *peri = self.scanPeripherals[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"name:%@, identifier:%@", peri.broadcast.mac, peri.broadcast.identifier];
    
    return cell;
}

// MARK: - UITableView Delegate {
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self connectPeripheral:self.scanPeripherals[indexPath.row]];
}

// Views
- (void)initViews {
    self.tableView = [[UITableView alloc] initWithFrame:self.view.frame];
    _tableView.dataSource = self;
    _tableView.delegate = self;
    _tableView.bounces = NO;
    _tableView.tableFooterView = [UIView new];
    [_tableView dequeueReusableCellWithIdentifier:@"cell"];
    [self.view addSubview:self.tableView];
}



@end
