#define FREQ_PWM_0_DEG_PHASE false
#define FREQ_PWM_180_DEG_PHASE true

class FreqPwm
{
private:
    int8_t m_timer = 0;
    int8_t m_Fr = 0;
    bool m_phase = false;
    long m_freq = 0;
    long m_top = 0;
public:
    long actFreq = 0;
    FreqPwm(int8_t timer,long Freq,bool phase)
    {
        m_timer = timer;
        m_freq = Freq;
        m_phase = phase;
    }
    void init()
    {
        switch (m_timer)
        {
        case 0:
            //DDRD |= (1 << PORTD5);
            if (!m_phase)
            {
                TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
                if (m_freq < 152 && m_freq > 0)
                {
                    m_Fr = 5;
                    actFreq = 61;
                }
                else if (m_freq >= 152 && m_freq < 610)
                {
                    m_Fr = 4;
                    actFreq = 244;
                }
                else if (m_freq >= 610 && m_freq < 4394)
                {
                    m_Fr = 3;
                    actFreq = 977;
                }
                else if (m_freq >= 4394 && m_freq < 35156)
                {
                    m_Fr = 2;
                    actFreq = 7812;
                }
                else if (m_freq >= 35156)
                {
                    m_Fr = 1;
                    actFreq = 62500;
                }
            }
            else
            {
                //180 deg phase
                TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00);
                if (m_freq < 77 && m_freq > 0)
                {
                    m_Fr = 5;
                    actFreq = 31;
                }
                else if (m_freq >= 77 && m_freq < 307)
                {
                    m_Fr = 4;
                    actFreq = 123;
                }
                else if (m_freq >= 307 && m_freq < 2206)
                {
                    m_Fr = 3;
                    actFreq = 490;
                }
                else if (m_freq >= 2206 && m_freq < 17647)
                {
                    m_Fr = 2;
                    actFreq = 3922;
                }
                else if (m_freq >= 17647)
                {
                    m_Fr = 1;
                    actFreq = 31373;
                }
            }
            TCCR0B = m_Fr;
            break;
        case 1:
            //DDRB |= (1 << PORTB1);
            cli();
            TCCR1A = 0;
            TCCR1B = 0;
            if (m_phase)
            {
                TCCR1B |= (1 << WGM13); //phase correct
                m_top = (16000000 / (2 * m_freq));
                TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM11);
                actFreq = 16000000 / (m_top + 1);
            }
            else
            {
                TCCR1B |= (1 << WGM13) | (1 << WGM12);
                m_top = (16000000 / (m_freq - 1));
                TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
                actFreq = 16000000 / 2 * (m_top);
            }
            ICR1 = m_top;
            TCCR1B |= 1;
            sei();
            break;
        case 2:
            //DDRD |= (1 << PORTD3);
            if (!m_phase)
            {
                TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
                if (m_freq < 152 && m_freq > 0)
                {
                    m_Fr = 7;
                    actFreq = 61;
                }
                else if (m_freq >= 152 && m_freq < 366)
                {
                    m_Fr = 6;
                    actFreq = 244;
                }
                else if (m_freq >= 366 && m_freq < 733)
                {
                    m_Fr = 5;
                    actFreq = 488;
                }
                else if (m_freq >= 733 && m_freq < 1465)
                {
                    m_Fr = 4;
                    actFreq = 977;
                }
                else if (m_freq >= 1456 && m_freq < 4883)
                {
                    m_Fr = 3;
                    actFreq = 1953;
                }
                else if (m_freq >= 4833 && m_freq < 35156)
                {
                    m_Fr = 2;
                    actFreq = 7812;
                }
                else if (m_freq >= 35156)
                {
                    m_Fr = 1;
                    actFreq = 62500;
                }
            }
            else
            {
                //180 deg pahse
                TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20);
                if (m_freq < 77 && m_freq > 0)
                {
                    m_Fr = 7;
                    actFreq = 31;
                }
                else if (m_freq >= 77 && m_freq < 184)
                {
                    m_Fr = 6;
                    actFreq = 123;
                }
                else if (m_freq >= 184 && m_freq < 368)
                {
                    m_Fr = 5;
                    actFreq = 245;
                }
                else if (m_freq >= 368 && m_freq < 735)
                {
                    m_Fr = 4;
                    actFreq = 490;
                }
                else if (m_freq >= 735 && m_freq < 2451)
                {
                    m_Fr = 3;
                    actFreq = 980;
                }
                else if (m_freq >= 2451 && m_freq < 17648)
                {
                    m_Fr = 2;
                    actFreq = 3922;
                }
                else if (m_freq >= 17648)
                {
                    m_Fr = 1;
                    actFreq = 31373;
                }
            }
            TCCR2B = m_Fr;
            break;
        }
    }
    void SetCycle(int8_t pin,int8_t Persentage)
    {
        switch(pin)
        {
            case 3:
                if (!m_phase)
                {
                    OCR2B = Persentage * 255 / 100;
                }
                else
                {
                    OCR2B = (100-Persentage) * 255 / 100;
                }
            break;
            case 5:
                if (!m_phase)
                {
                    OCR0B = Persentage * 255 / 100;
                }
                else
                {
                    OCR0B = (100 - Persentage) * 255 / 100;
                }
            break;
            case 6:
              OCR0A = Persentage * 255 / 100;
            break;
            case 9:
              cli();
              OCR1A = (Persentage * m_top / 100L);
              sei();
            break;
            case 10:
              cli();
              if (!m_phase)
              {
                  OCR1B = (Persentage * m_top / 100L);
              }
              else
              {
                  OCR1B = ((100 - Persentage) * m_top / 100L);
              }
              sei();
            break;
            case 11:
              OCR2A = Persentage * 255 / 100;
            break;
        }
    }
};
