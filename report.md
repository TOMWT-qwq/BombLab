## BombLab 实验报告

> ——吴童 25803050055

### 实验成果

### 实验过程

#### 01

```
  4020d3:	cmp    $0x1,%eax
```

看出需要一个整形。

```

0000000000402020 <p1_step0>:
  402020:	endbr64 
  402024:	sub    %esi,%edi
  402026:	lea    0x31b(%rdi,%rdi,4),%eax
  40202d:	retq   
  40202e:	xchg   %ax,%ax

0000000000402030 <p1_step1>:
  402030:	endbr64 
  402034:	lea    (%rdi,%rdi,4),%eax
  402037:	add    $0x1a90,%esi
  40203d:	xor    %esi,%eax
  40203f:	retq   

0000000000402040 <p1_step2>:
  402040:	endbr64 
  402044:	lea    (%rdi,%rsi,2),%eax
  402047:	xor    $0x548e,%eax
  40204c:	retq   
  40204d:	nopl   (%rax)

0000000000402050 <p1_compute>:
  402050:	endbr64 
  402054:	push   %rbp
  402055:	mov    %rdi,%rax
  402058:	mov    %rdi,%rdx
  40205b:	mov    %edi,%r8d
  40205e:	shr    $0x20,%rax
  402062:	shr    $0x10,%rdx
  402066:	mov    %eax,%r9d
  402069:	mov    %eax,%esi
  40206b:	mov    %rsp,%rbp
  40206e:	callq  402020 <p1_step0>
  402073:	mov    %rdx,%rsi
  402076:	mov    %r9d,%edi
  402079:	mov    %eax,%ecx
  40207b:	callq  402030 <p1_step1>
  402080:	mov    %r8d,%esi
  402083:	mov    %eax,%edi
  402085:	callq  402040 <p1_step2>
  40208a:	pop    %rbp
  40208b:	xor    %ecx,%eax
  40208d:	retq   
  40208e:	xchg   %ax,%ax
```

这四个函数直接翻译成 C 语言代码即可。

#### 02

```
  402155:	cmp    $0x6,%eax
```

看出需要六个整形。

```
  40215a:	mov    %r13,%rdx
  40215d:	mov    -0x40(%rbp),%eax
  402160:	shr    $0x25,%rdx
  402164:	movzbl %dl,%edx
  402167:	xor    $0x19,%edx
  40216a:	cmp    %edx,%eax
  40216c:	jne    402115 <phase_02+0x25>
  40216e:	mov    $0x16,%ecx
  402173:	mov    $0x1,%edx
  402178:	mov    %r13,%rdi
  40217b:	add    %edx,%eax
  40217d:	shr    %cl,%rdi
  402180:	lea    (%rax,%rax,2),%eax
  402183:	and    $0x3f,%edi
  402186:	sub    %edi,%eax
  402188:	mov    %eax,%esi
  40218a:	mov    -0x40(%rbp,%rdx,4),%eax
  40218e:	cmp    %esi,%eax
  402190:	jne    402115 <phase_02+0x25>
  402192:	add    $0x1,%rdx
  402196:	add    $0x5,%ecx
  402199:	cmp    $0x6,%rdx
  40219d:	jne    402178 <phase_02+0x88>
```

`jne    402178` 这里是一个 `dowhile` 循环。应该是第一个数单独算出来，然后循环五次产生其余五个数。

#### 03

```
  4022e7:	cmp    $0x2,%eax
```

看出来要两个整形。

```
  4022ec:	mov    %r12d,%edi
  4022ef:	xor    %eax,%eax
  4022f1:	and    $0x7,%edi
```

第一个数应该就是 `challenge&7`。

```
  4022f9:	mov    %r12,%rax
  4022fc:	mov    %r12,%rsi
  4022ff:	shr    $0x3,%rax
  402303:	shr    $0x20,%rsi
  402307:	xor    %eax,%esi
  402309:	callq  402240 <p3_dispatch>
```

```
00000000004021b0 <p3_case_0>:
  4021b0:	endbr64 
  4021b4:	lea    (%rdi,%rdi,1),%eax
  4021b7:	xor    $0x70e5,%eax
  4021bc:	retq   
  4021bd:	nopl   (%rax)

00000000004021c0 <p3_case_1>:
  4021c0:	endbr64 
  4021c4:	lea    0x44c9b(%rdi,%rdi,4),%eax
  4021cb:	retq   
  4021cc:	nopl   0x0(%rax)

00000000004021d0 <p3_case_2>:
  4021d0:	endbr64 
  4021d4:	mov    %edi,%eax
  4021d6:	shr    %edi
  4021d8:	xor    $0x162b,%eax
  4021dd:	add    %edi,%eax
  4021df:	retq   

00000000004021e0 <p3_case_3>:
  4021e0:	endbr64 
  4021e4:	lea    0xc962(%rdi,%rdi,2),%eax
  4021eb:	retq   
  4021ec:	nopl   0x0(%rax)

00000000004021f0 <p3_case_4>:
  4021f0:	endbr64 
  4021f4:	mov    %edi,%eax
  4021f6:	shr    %edi
  4021f8:	xor    $0x7543,%eax
  4021fd:	add    %edi,%eax
  4021ff:	retq   

0000000000402200 <p3_case_5>:
  402200:	endbr64 
  402204:	lea    0xd881(%rdi,%rdi,4),%eax
  40220b:	retq   
  40220c:	nopl   0x0(%rax)

0000000000402210 <p3_case_6>:
  402210:	endbr64 
  402214:	lea    0x0(,%rdi,4),%eax
  40221b:	xor    $0xe829,%eax
  402220:	retq   
  402221:	data16 nopw %cs:0x0(%rax,%rax,1)
  40222c:	nopl   0x0(%rax)

0000000000402230 <p3_case_7>:
  402230:	endbr64 
  402234:	lea    0x18f9(%rdi,%rdi,2),%eax
  40223b:	retq   
  40223c:	nopl   0x0(%rax)

0000000000402240 <p3_dispatch>:
  402240:	endbr64 
  402244:	mov    %edi,%eax
  402246:	mov    %esi,%edi
  402248:	cmp    $0x7,%eax
  40224b:	ja     402295 <p3_dispatch+0x55>
  40224d:	notrack jmpq *0x405820(,%rax,8)
  402255:	nopl   (%rax)
  402258:	jmp    4021e0 <p3_case_3>
  40225a:	nopw   0x0(%rax,%rax,1)
  402260:	jmp    402230 <p3_case_7>
  402262:	nopw   0x0(%rax,%rax,1)
  402268:	jmpq   4021c0 <p3_case_1>
  40226d:	nopl   (%rax)
  402270:	jmp    402200 <p3_case_5>
  402272:	nopw   0x0(%rax,%rax,1)
  402278:	jmpq   4021f0 <p3_case_4>
  40227d:	nopl   (%rax)
  402280:	jmpq   4021b0 <p3_case_0>
  402285:	nopl   (%rax)
  402288:	jmpq   4021d0 <p3_case_2>
  40228d:	nopl   (%rax)
  402290:	jmpq   402210 <p3_case_6>
  402295:	xor    %eax,%eax
  402297:	retq   
  402298:	nopl   0x0(%rax,%rax,1)

```

看上去是一坨 `switch-case`。直接翻译成 C 语言就行了。

一个比较有趣的地方是，用 `callq` 调用了 `dispatch`，但是 `dispatch` 转到 `case` 的时候用的是 `jmpq`，然后执行 `case` 里的 `retq` 的时候会回到 `callq` 的位置，而不是 `jmpq`。

注意 `jmpq *0x405820(,%rax,8)` 会去查 `0x405820` 为起始地址的一个表，那里存的是从 `0x402258` 开始的一系列地址。

#### 04

```
  4023d3:	cmp    $0x1,%eax
```

看出来只有一个整形。

并且是直接和 `p4_walk` 的返回值比较。

```
  4023d8:	mov    %r12,%rcx
  4023db:	mov    %r12,%rax
  4023de:	mov    %r12d,%edi
  4023e1:	xor    %esi,%esi
  4023e3:	shr    $0x20,%rax
  4023e7:	shr    $0x7,%rcx
  4023eb:	and    $0x7f,%edi
  4023ee:	mov    $0x7f,%edx
  4023f3:	xor    %eax,%ecx
```

参数初值依次为 `challenge&0x7f,0,0x7f,(challenge>>7)^(challenge>>32)`。

```
0000000000402320 <p4_walk>:
  402320:	endbr64 
  402324:	mov    %edi,%eax
  402326:	mov    %edx,%edi
  402328:	sub    %esi,%edi
  40232a:	shr    %edi
  40232c:	add    %esi,%edi
  40232e:	cmp    %eax,%edi
  402330:	je     402380 <p4_walk+0x60>
  402332:	push   %rbp
  402333:	mov    %rsp,%rbp
  402336:	push   %rbx
  402337:	lea    (%rdi,%rcx,1),%ebx
  40233a:	sub    $0x8,%rsp
  40233e:	cmp    %edi,%eax
  402340:	jb     402360 <p4_walk+0x40>
  402342:	lea    0x1(%rdi),%esi
  402345:	mov    %eax,%edi
  402347:	callq  402320 <p4_walk>
  40234c:	lea    (%rax,%rax,4),%eax
  40234f:	xor    %ebx,%eax
  402351:	mov    -0x8(%rbp),%rbx
  402355:	leaveq 
  402356:	xor    $0x1f,%eax
  402359:	retq   
  40235a:	nopw   0x0(%rax,%rax,1)
  402360:	lea    -0x1(%rdi),%edx
  402363:	mov    %eax,%edi
  402365:	callq  402320 <p4_walk>
  40236a:	lea    (%rax,%rax,4),%eax
  40236d:	xor    %ebx,%eax
  40236f:	mov    -0x8(%rbp),%rbx
  402373:	leaveq 
  402374:	xor    $0x13,%eax
  402377:	retq   
  402378:	nopl   0x0(%rax,%rax,1)
  402380:	lea    0x6b(%rdi),%eax
  402383:	xor    %ecx,%eax
  402385:	retq   
  402386:	nopw   %cs:0x0(%rax,%rax,1)
```

`walk` 翻译之后应该是在 `0` 和 `0x7f` 之间二分查找 `challenge&7`。注意不要漏掉返回之后的操作。

#### 05

```
  4024b7:	cmp    $0x2,%eax
```

看出来要两个整形。其中第一个是 `traverse` 的返回值，另一个用指针传出来。`lea    -0x14(%rbp),%rsi` 看出第二个参数是个指针。

```
0000000000402410 <p5_traverse>:
  402410:	endbr64 
  402414:	mov    %rdi,%rax
  402417:	mov    %rdi,%rcx
  40241a:	mov    %rsi,%r8
  40241d:	and    $0x7,%eax
  402420:	shr    $0x3,%rcx
  402424:	mov    0x405b60(,%rax,8),%rdx
  40242c:	mov    %rdi,%rax
  40242f:	shr    $0x20,%rdi
  402433:	shr    $0x6,%rax
  402437:	mov    0x8(%rdx),%esi
  40243a:	xor    %edi,%eax
  40243c:	xor    0xc(%rdx),%eax
  40243f:	mov    %ecx,%edi
  402441:	xor    $0xc1,%ah
  402444:	mov    %esi,(%r8)
  402447:	add    %esi,%eax
  402449:	and    $0x3,%edi
  40244c:	je     402468 <p5_traverse+0x58>
  40244e:	mov    $0x1,%ecx
  402453:	mov    (%rdx),%rdx
  402456:	add    $0x1,%ecx
  402459:	mov    0x8(%rdx),%esi
  40245c:	xor    0xc(%rdx),%eax
  40245f:	add    %esi,%eax
  402461:	mov    %esi,(%r8)
  402464:	cmp    %ecx,%edi
  402466:	jae    402453 <p5_traverse+0x43>
  402468:	retq   
  402469:	nopl   0x0(%rax)
```

`traverse` 就是在遍历一个静态的链表。需要费点功夫把链表里的数据给找出来，然后把汇编翻译成 C 语言就可以了。

#### 6

```
  4025f3:	cmp    $0x1,%eax
```

看起来只要一个整形。

```
00000000004024e0 <p6_op_0>:
  4024e0:	endbr64 
  4024e4:	mov    %edi,%eax
  4024e6:	lea    (%rdi,%rdi,4),%edx
  4024e9:	shl    $0x5,%eax
  4024ec:	add    $0x1a51,%eax
  4024f1:	xor    %edx,%eax
  4024f3:	retq   
  4024f4:	data16 nopw %cs:0x0(%rax,%rax,1)
  4024ff:	nop

0000000000402500 <p6_op_1>:
  402500:	endbr64 
  402504:	mov    %edi,%eax
  402506:	shl    $0x5,%edi
  402509:	xor    $0x5797,%eax
  40250e:	add    %edi,%eax
  402510:	retq   
  402511:	data16 nopw %cs:0x0(%rax,%rax,1)
  40251c:	nopl   0x0(%rax)

0000000000402520 <p6_op_2>:
  402520:	endbr64 
  402524:	mov    %edi,%eax
  402526:	rol    $0x2,%eax
  402529:	xor    $0xe1e1,%eax
  40252e:	retq   
  40252f:	nop

0000000000402530 <p6_op_3>:
  402530:	endbr64 
  402534:	mov    %edi,%eax
  402536:	ror    $0x3,%eax
  402539:	retq   
  40253a:	nopw   0x0(%rax,%rax,1)

0000000000402540 <p6_op_4>:
  402540:	endbr64 
  402544:	mov    %edi,%eax
  402546:	shr    %eax
  402548:	xor    %edi,%eax
  40254a:	add    $0x70d8,%eax
  40254f:	retq   

0000000000402550 <p6_op_5>:
  402550:	endbr64 
  402554:	lea    0xa941(%rdi),%eax
  40255a:	shr    %edi
  40255c:	xor    %edi,%eax
  40255e:	retq   
  40255f:	nop
```

这六个直接翻译成 C 语言代码。注意实现 `rol` 和 `ror`。

```
0000000000402560 <p6_dispatch>:
  402560:	endbr64 
  402564:	push   %rbp
  402565:	mov    %rsp,%rbp
  402568:	push   %rbx
  402569:	mov    %rdi,%rbx
  40256c:	shr    $0x6,%rdi
  402570:	mov    %rbx,%rax
  402573:	shr    $0x20,%rax
  402577:	xor    %eax,%edi
  402579:	mov    %rbx,%rax
  40257c:	sub    $0x8,%rsp
  402580:	and    $0x38,%ebx
  402583:	and    $0x7,%eax
  402586:	callq  *0x405e00(,%rax,8)
  40258d:	xor    $0xaedb,%eax
  402592:	mov    %eax,%edi
  402594:	callq  *0x405e00(%rbx)
  40259a:	mov    -0x8(%rbp),%rbx
  40259e:	leaveq 
  40259f:	add    $0x56e4,%eax
  4025a4:	retq   
  4025a5:	data16 nopw %cs:0x0(%rax,%rax,1)
```

除了把函数指针数组扒出来以外，还要注意 `*0x405e00(%rbx)` 这里访问的是 `0x405e00+%rbx`，与上面一处调用不同。

#### Honor

```
  402751:	sub    $0x24,%rax
  402755:	cmp    $0x7f,%rax
```

这里应该是要求字符串长度在 36 到 36+127 之间。

```
00000000004026f0 <secret_copy>:
  4026f0:	endbr64 
  4026f4:	xor    %eax,%eax
  4026f6:	nopw   %cs:0x0(%rax,%rax,1)
  402700:	movzbl (%rsi,%rax,1),%edx
  402704:	mov    %dl,(%rdi,%rax,1)
  402707:	add    $0x1,%rax
  40270b:	test   %dl,%dl
  40270d:	jne    402700 <secret_copy+0x10>
  40270f:	retq   
```

`secret_copy` 是逐字节赋值，应该类似 `strcpy`？

```
0000000000402710 <secret_gate>:
  402710:	endbr64 
  402714:	push   %rbp
  402715:	xor    %eax,%eax
  402717:	mov    $0x14,%ecx
  40271c:	mov    %rsp,%rbp
  40271f:	push   %r14
  402721:	mov    %rdx,%r14
  402724:	push   %r13
  402726:	mov    %rsi,%r13
  402729:	push   %r12
  40272b:	lea    -0xd0(%rbp),%r12
  402732:	push   %rbx
  402733:	mov    %rdi,%rbx
  402736:	mov    %r12,%rdi
  402739:	sub    $0xb0,%rsp
  402740:	rep stos %rax,%es:(%rdi)
  402743:	movl   $0x0,(%rdi)
  402749:	mov    %rbx,%rdi
  40274c:	callq  401190 <_init+0x190>
  402751:	sub    $0x24,%rax
  402755:	cmp    $0x7f,%rax
  402759:	jbe    402770 <secret_gate+0x60>
  40275b:	add    $0xb0,%rsp
  402762:	xor    %eax,%eax
  402764:	pop    %rbx
  402765:	pop    %r12
  402767:	pop    %r13
  402769:	pop    %r14
  40276b:	pop    %rbp
  40276c:	retq   
  40276d:	nopl   (%rax)
  402770:	mov    %rbx,%rsi
  402773:	mov    %r12,%rdi
  402776:	callq  4026f0 <secret_copy>
  40277b:	cmpl   $0x4e45504f,-0xb0(%rbp)
  402785:	jne    40275b <secret_gate+0x4b>
  402787:	mov    %r14,%rdx
  40278a:	mov    %r13,%rsi
  40278d:	lea    -0xac(%rbp),%rdi
  402794:	callq  402630 <secret_phase>
  402799:	add    $0xb0,%rsp
  4027a0:	pop    %rbx
  4027a1:	pop    %r12
  4027a3:	pop    %r13
  4027a5:	pop    %r14
  4027a7:	pop    %rbp
  4027a8:	retq   
  4027a9:	nopl   0x0(%rax)
```

结果就是在栈上开了长为 `0xb0` 的空间，然后从 `-0xd0` 的位置开始复制字符串，那么最前面的 32 个字符应该就丢掉了。然后接下来从 `-0xb0` 开始的四个字节必须恰好等于 `0x4e45504f`。然后从 `-0xac` 开始都交给 `secret_phase` 去检查？

剩下来的类似前面的题目了：

```
0000000000402610 <secret_mix>:
  402610:	endbr64 
  402614:	mov    %edi,%eax
  402616:	xor    $0xd3b3,%edi
  40261c:	shr    $0x5,%eax
  40261f:	xor    $0xf44d,%eax
  402624:	add    %edi,%eax
  402626:	retq   
  402627:	nopw   0x0(%rax,%rax,1)
```

直接翻译成 C 语言。

```
  40268b:	cmp    $0x3,%eax
```

看起来有三个整形。

```
  402690:	mov    %r13d,%ecx
  402693:	xor    %edx,%edx
  402695:	and    $0x3,%ecx
  402698:	cmp    %ecx,-0x2c(%rbp)
  40269b:	jne    40265a <secret_phase+0x2a>
  40269d:	mov    %r12,%rsi
  4026a0:	imul   $0xd3b3,%ecx,%r9d
  4026a7:	mov    %r13,%r8
  4026aa:	shr    $0x20,%rsi
  4026ae:	shr    $0x20,%r8
  4026b2:	xor    %r12d,%esi
  4026b5:	xor    %r13d,%r8d
  4026b8:	shr    $0x10,%r13
  4026bc:	mov    %esi,%edi
  4026be:	xor    %r13d,%r9d
  4026c1:	xor    %r8d,%edi
  4026c4:	callq  402610 <secret_mix>
  4026c9:	xor    %r9d,%eax
  4026cc:	cmp    %eax,-0x28(%rbp)
  4026cf:	jne    40265a <secret_phase+0x2a>
  4026d1:	shr    $0x5,%esi
  4026d4:	lea    0xf44d(%r8,%rcx,1),%edx
  4026dc:	add    %esi,%edx
  4026de:	xor    %edx,%eax
  4026e0:	cmp    -0x24(%rbp),%eax
  4026e3:	sete   %dl
  4026e6:	jmpq   40265a <secret_phase+0x2a>
```

翻译成 C 语言即可。

一个问题是我其实看不出来最初的 `%rsi` 和 `%rdx` 哪个是 `challenge` 哪个是 `context`。只能两个都试一遍。

### 总结与感想

这次 Lab 真的很困难很累人。大部分时候都只能一句一句硬翻译。

部分题目借助了人工智能工具来理解汇编代码，但是很多时候人工智能工具也不靠谱。比如 Honor 题它就试图去分辨那两个输入量。